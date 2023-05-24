/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:35:32 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/10 10:03:43 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	whole_read_write(int read_fd, int write_fd)
{
	char	*buffer;

	buffer = get_next_line(read_fd);
	while (buffer != NULL)
	{
		write(write_fd, buffer, ft_strlen(buffer));
		free(buffer);
		buffer = get_next_line(read_fd);
	}
}

static char	*read_untill_limiter(t_arg *args, const char *suffix)
{
	char	*buffer;
	char	*tmp;
	char	*curr;

	buffer = NULL;
	write(1, suffix, ft_strlen(suffix));
	curr = get_next_line(0);
	while (curr == NULL || ft_strcmp(curr, args->cmds[0][0]) != 0)
	{
		if (curr != NULL && ft_strchr(curr, '\n') != NULL)
			write(1, suffix, ft_strlen(suffix));
		if (buffer == NULL)
			buffer = curr;
		else if (curr != NULL)
		{
			tmp = ft_strjoin(buffer, curr);
			if (tmp == NULL)
				print_error(ERR_MALLOC, NULL);
			free(buffer);
			free(curr);
			buffer = tmp;
		}
		curr = get_next_line(0);
	}
	return (free(curr), buffer);
}

int	pipe_line(t_arg *args, char **env)
{
	int		cnt;
	int		exit_status;

	cnt = 0;
	file_to_pipe(args);
	while (cnt < args->cmd_count - 1)
	{
		pipe_mulit_process(args, cnt, env);
		cnt++;
	}
	exit_status = pipe_to_file(args, cnt, env);
	return (exit_status);
}

static char	*concat_suffix(t_arg *args)
{
	int		i;
	char	*suffix;
	char	*tmp;

	suffix = malloc(sizeof(char) * 10);
	if (suffix == NULL)
		print_error(ERR_MALLOC, NULL);
	ft_strlcpy(suffix, "heredoc> ", 10);
	i = 1;
	while (i < args->cmd_count - 1)
	{
		tmp = ft_strjoin("pipe ", suffix);
		if (tmp == NULL)
			print_error(ERR_MALLOC, NULL);
		free(suffix);
		suffix = tmp;
		i++;
	}
	return (suffix);
}

int	here_doc(t_arg *args, char **env)
{
	int		cnt;
	char	*suffix;
	char	*buffer;
	int		exit_status;

	if (args->cmd_count == 1)
		print_error(ERR_PARAM, NULL);
	suffix = concat_suffix(args);
	buffer = read_untill_limiter(args, suffix);
	free(suffix);
	cnt = 1;
	str_to_pipe(buffer);
	while (cnt < args->cmd_count - 1)
	{
		pipe_mulit_process(args, cnt, env);
		cnt++;
	}
	exit_status = pipe_to_file(args, cnt, env);
	return (exit_status);
}
