/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_restore.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 10:17:34 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/05 15:31:32 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect_save_origin(t_token *tokens)
{
	tokens->stdin_origin = dup(STDIN_FILENO);
	tokens->stdout_origin = dup(STDOUT_FILENO);
}

int	redirect_in_restore(t_token *tokens)
{
	if (close(STDIN_FILENO) < 0)
		return (-1);
	if (dup2(tokens->stdin_origin, STDIN_FILENO) < 0)
		return (-1);
	close(tokens->stdin_origin);
	return (0);
}

int	redirect_out_restore(t_token *tokens)
{
	if (close(STDOUT_FILENO) < 0)
		return (-1);
	if (dup2(tokens->stdout_origin, STDOUT_FILENO) < 0)
		return (-1);
	close(tokens->stdout_origin);
	return (0);
}

void	pipe_wait(int *status, pid_t pid, int cmd_cnt)
{
	int	i;

	if (*status != -1)
		waitpid(pid, status, 0);
	else
		waitpid(pid, NULL, 0);
	i = 0;
	while (++i < cmd_cnt)
		wait(NULL);
}
