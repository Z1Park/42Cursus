/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 10:15:00 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/27 15:58:28 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	close_pipe(int p_fd[2])
{
	if (close(p_fd[0]) < 0)
		print_error(ERR_CLOSE, NULL);
	if (close(p_fd[1]) < 0)
		print_error(ERR_CLOSE, NULL);
}

void	file_to_pipe(t_arg *args)
{
	pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) < 0)
		print_error(ERR_PIPE, NULL);
	pid = fork();
	if (pid < 0)
		print_error(ERR_FORK, NULL);
	else if (pid > 0)
	{
		if (waitpid(pid, NULL, WNOHANG) == -1)
			print_error(ERR_CHILD_FAIL, NULL);
		if (dup2(p_fd[0], STDIN_FILENO) < 0)
			print_error(ERR_DUP, NULL);
		close_pipe(p_fd);
	}
	else
	{
		whole_read_write(args->in_fd, p_fd[1]);
		close_pipe(p_fd);
		exit(0);
	}
}

void	str_to_pipe(char *buffer)
{
	pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) < 0)
		print_error(ERR_PIPE, NULL);
	pid = fork();
	if (pid < 0)
		print_error(ERR_FORK, NULL);
	else if (pid > 0)
	{
		if (waitpid(pid, NULL, WNOHANG) == -1)
			print_error(ERR_CHILD_FAIL, NULL);
		if (dup2(p_fd[0], STDIN_FILENO) < 0)
			print_error(ERR_DUP, NULL);
		close_pipe(p_fd);
	}
	else
	{
		write(p_fd[1], buffer, ft_strlen(buffer));
		close_pipe(p_fd);
		exit(0);
	}
	free(buffer);
}

void	pipe_mulit_process(t_arg *args, int cnt, char **env)
{
	pid_t	pid;
	int		p_fd[2];

	if (pipe(p_fd) < 0)
		print_error(ERR_PIPE, NULL);
	pid = fork();
	if (pid < 0)
		print_error(ERR_FORK, NULL);
	else if (pid > 0)
	{
		if (dup2(p_fd[0], STDIN_FILENO) < 0)
			print_error(ERR_DUP, NULL);
		close_pipe(p_fd);
	}
	else
	{
		if (dup2(p_fd[1], STDOUT_FILENO) < 0)
			print_error(ERR_DUP, NULL);
		close_pipe(p_fd);
		if (execve(args->paths[cnt], args->cmds[cnt], env) < 0)
			print_error(ERR_CHILD_FAIL, NULL);
	}
}

int	pipe_to_file(t_arg *args, int cnt, char **env)
{
	pid_t	pid;
	int		p_fd[2];
	int		status;

	status = 0;
	if (pipe(p_fd) < 0)
		print_error(ERR_PIPE, NULL);
	pid = fork();
	if (pid < 0)
		print_error(ERR_FORK, NULL);
	else if (pid > 0)
	{
		close_pipe(p_fd);
	}
	else
	{
		if (dup2(args->out_fd, STDOUT_FILENO) < 0)
			print_error(ERR_DUP, NULL);
		close_pipe(p_fd);
		status = execve(args->paths[cnt], args->cmds[cnt], env);
		print_error(ERR_CHILD_FAIL, NULL);
	}
	return (status);
}
