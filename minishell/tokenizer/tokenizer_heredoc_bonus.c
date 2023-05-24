/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_heredoc_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:21:31 by heejikim          #+#    #+#             */
/*   Updated: 2023/01/07 11:11:06 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	convert_and_write(int fd, char *rd_buf, int conv_flag)
{
	size_t	i;

	if (conv_flag == 0)
	{
		write(fd, rd_buf, ft_strlen(rd_buf));
		return ;
	}
	while (*rd_buf != '\0')
	{
		if (*rd_buf == '$')
		{
			if (ft_strchr(" &|<>$+=.,\'\"\n\0", *rd_buf) == NULL)
			{
				rd_buf++;
				i = get_len_until_chr(rd_buf, '\n');
				find_key_and_write(fd, rd_buf, i);
			}
			else
				i = write_until_dollor(rd_buf, fd, 1);
			rd_buf += i;
			continue ;
		}
		i = write_until_dollor(rd_buf, fd, 0);
		rd_buf += i;
	}
}

void	write_heredoc(void (*old_si)(int), char *filename, char *eof, \
					int conv_flag)
{
	int		fd;
	char	*rd_buf;

	signal(SIGINT, old_si);
	signal(SIGQUIT, SIG_IGN);
	fd = write_redirect(filename, O_TRUNC);
	if (!eof || fd < 0)
		quit_shell(1);
	rd_buf = ft_readline();
	while (rd_buf && ft_strcmp(rd_buf, eof) != 0)
	{
		convert_and_write(fd, rd_buf, conv_flag);
		safe_free(rd_buf);
		rd_buf = ft_readline();
	}
	if (rd_buf)
		safe_free(rd_buf);
	close(fd);
	quit_shell(0);
}

int	read_heredoc(t_token_list *list, void (*old_si)(int), char *eof, \
				int conv_flag)
{
	int		fd;
	pid_t	pid;
	int		status;
	char	*filename;

	filename = heredoc_filename();
	pid = fork();
	if (pid < 0)
	{
		print_error(ERR_FORK, NULL);
		return (-1);
	}
	else if (pid == 0)
		write_heredoc(old_si, filename, eof, conv_flag);
	waitpid(pid, &status, 0);
	fd = read_redirect(filename);
	safe_free(filename);
	if (status != 0)
	{
		write(1, "\n", 1);
		change_env_value("?", ft_itoa(EXIT_NORMAL_ERR));
		list->interrupted = 1;
	}
	return (fd);
}

char	*parse_heredoc(const char **str, int *conv_flag)
{
	char	*result;
	size_t	len;

	len = get_delimitter_len(*str);
	result = copy_delimitter(str, len, conv_flag);
	return (result);
}

void	get_heredoc(t_token_list *list, const char **str, void (*old_si)(int))
{
	char	*eof;
	int		fd;
	int		conv_flag;

	*str += 2;
	skip_space(str);
	eof = parse_heredoc(str, &conv_flag);
	if (list->tokens[list->size - 1]->cur_pipe->redirect_in != 0)
	{
		close(list->tokens[list->size - 1]->cur_pipe->redirect_in);
		list->tokens[list->size - 1]->cur_pipe->redirect_in = 0;
	}
	g_sys.reading_flag = HEREDOC;
	fd = read_heredoc(list, old_si, eof, conv_flag);
	g_sys.reading_flag = IDLE;
	if (fd > 0)
		list->tokens[list->size - 1]->cur_pipe->redirect_in = fd;
	else
		list->tokens[list->size - 1]->cur_pipe->result = TOKEN_RD_FAIL;
	safe_free(eof);
}
