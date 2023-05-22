/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_outfile.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejikim <heejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 10:58:02 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/04 18:53:20 by heejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_file_access(char *filename)
{
	char	*tmp;
	char	*dir;

	tmp = ft_strrchr(filename, '/');
	if (tmp != NULL)
	{
		dir = safe_malloc(sizeof(char) * (tmp - filename + 1));
		ft_strlcpy(dir, filename, tmp - filename + 1);
		if (access(dir, F_OK) == -1)
		{
			print_error(ERR_NO_FILE, filename);
			safe_free(dir);
			return (-1);
		}
		safe_free(dir);
	}
	return (0);
}

int	write_redirect(char *filename, int append_flag)
{
	int	fd;

	if (!filename)
		return (-1);
	if (check_file_access(filename) < 0)
		return (-1);
	fd = open(filename, O_RDWR | O_CREAT | append_flag, 0644);
	if (fd < 0)
	{
		print_error(ERR_AUTH_FAIL, filename);
		return (-1);
	}
	return (fd);
}

void	get_outfile(t_token *token, const char **str, int append_flag)
{
	char	*filename;

	(*str) += 1 + (*(*str + 1) == '>');
	skip_space(str);
	filename = parse_filename(token, str);
	if (token->cur_pipe->redirect_out != 1)
	{
		close(token->cur_pipe->redirect_out);
		token->cur_pipe->redirect_out = 1;
	}
	token->cur_pipe->redirect_out = write_redirect(filename, append_flag);
	if (token->cur_pipe->redirect_out < 0)
	{
		token->cur_pipe->redirect_out = -1;
		token->cur_pipe->result = TOKEN_WR_FAIL;
	}
	safe_free(filename);
}
