/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 10:52:38 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/06 17:40:06 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/wait.h>
#include "minishell.h"
#include <termios.h>

static void	parent_process(__attribute__((unused)) t_pipe *token, int p_fd[])
{
	if (dup2(p_fd[READ], STDIN_FILENO) < 0)
		print_error(ERR_DUP, NULL);
	close(p_fd[READ]);
	close(p_fd[WRITE]);
}

static void	child_process(char *cmd_path, t_pipe *token, int p_fd[])
{
	if (token->result == TOKEN_SUCCESS && token->redirect_out > WRITE)
	{
		if (dup2(token->redirect_out, STDOUT_FILENO) < 0)
			print_error(ERR_DUP, NULL);
		close(token->redirect_out);
	}
	else if (token->result == TOKEN_SUCCESS && token->next != NULL)
	{
		if (dup2(p_fd[WRITE], STDOUT_FILENO) < 0)
			print_error(ERR_DUP, NULL);
	}
	close(p_fd[WRITE]);
	close(p_fd[READ]);
	if (token->argc == 0)
		write(STDOUT_FILENO, "", 1);
	else if (token->result == TOKEN_SUCCESS && token->redirect_out != -1
		&& is_builtin(token->argv[0]) == TRUE)
		exe_builtin(token);
	else if (token->result == TOKEN_SUCCESS && token->redirect_out != -1)
		execve(cmd_path, token->argv, g_sys.p_env);
	quit_shell(ft_atoi(get_env_val("?")));
}

static int	fork_and_execve(char *cmd_path, t_pipe *token)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) < 0)
		print_error(ERR_PIPE, NULL);
	if (token->result == TOKEN_SUCCESS && token->redirect_in > READ)
	{
		if (dup2(token->redirect_in, STDIN_FILENO) < 0)
			print_error(ERR_DUP, NULL);
		close(token->redirect_in);
	}
	pid = fork();
	if (pid < 0)
		print_error(ERR_FORK, NULL);
	else if (pid > 0)
		parent_process(token, p_fd);
	else
	{
		if (cmd_path == NULL)
			child_process(token->argv[0], token, p_fd);
		else
			child_process(cmd_path, token, p_fd);
	}
	return (pid);
}

static int	cmd_process(t_pipe *pipes, int cmd_cnt, char **cmd_path)
{
	int		i;
	pid_t	pid;
	int		status;

	i = 0;
	status = 0;
	while (i < cmd_cnt)
	{
		if (cmd_path == NULL && is_builtin(pipes->argv[0]) == FALSE
			&& access(pipes->argv[0], F_OK) != 0)
			print_error(ERR_NO_FILE, pipes->argv[0]);
		else
		{
			pid = fork_and_execve(cmd_path[i], pipes);
			if (pid == -2)
				status = -1;
			if (cmd_path[i] != NULL)
				safe_free(cmd_path[i]);
		}
		pipes = pipes->next;
		i++;
	}
	pipe_wait(&status, pid, cmd_cnt);
	return (status);
}

void	do_commands(t_token *tokens)
{
	int		status;
	int		cmd_count;
	char	**cmd_path;

	redirect_save_origin(tokens);
	if (check_need_fork(tokens) == 1)
		return ;
	check_cmd_in_builtin_env(tokens);
	status = 0;
	cmd_count = get_cmd_count(tokens->pipes);
	cmd_path = token_to_cmd_path(tokens->pipes, cmd_count);
	status = cmd_process(tokens->pipes, cmd_count, cmd_path);
	if (status != -1)
	{
		if ((status & 0177) == 0)
			status = (status >> 8) & 0xff;
		else if ((status & 0177) != 0 && (status & 0177) != 0177)
			status = 128 + (status & 0177);
		change_env_value("?", ft_itoa(status));
	}
	safe_free(cmd_path);
	redirect_in_restore(tokens);
	redirect_out_restore(tokens);
}
