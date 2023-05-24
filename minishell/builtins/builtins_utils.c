/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejikim <heejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 09:05:35 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/04 16:04:55 by heejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(const char *cmd)
{
	const char	*builtins[] = {"echo", "cd", "pwd", \
		"exit", "env", "export", "unset"};
	size_t		i;

	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(cmd, builtins[i]) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	check_cmd_in_builtin_env(t_token *tokens)
{
	int		i;
	t_pipe	*pipe;
	char	**n_argv;

	pipe = tokens->pipes;
	while (pipe != NULL)
	{
		if (pipe->argc > 1
			&& ft_strcmp(pipe->argv[0], "env") == 0)
		{
			n_argv = safe_malloc(sizeof(char *) * (pipe->argc));
			i = 0;
			while (i < pipe->argc - 1)
			{
				n_argv[i] = ft_strdup(pipe->argv[i + 1]);
				i++;
			}
			n_argv[pipe->argc - 1] = NULL;
			free_splited(pipe->argv, pipe->argc);
			pipe->argc -= 1;
			pipe->argv = n_argv;
		}
		pipe = pipe->next;
	}
}

void	exe_builtin(t_pipe *token)
{
	if (ft_strcmp(token->argv[0], "echo") == 0)
		builtin_echo(token);
	else if (ft_strcmp(token->argv[0], "cd") == 0)
		builtin_cd(token, 0);
	else if (ft_strcmp(token->argv[0], "pwd") == 0)
		builtin_pwd(token);
	else if (ft_strcmp(token->argv[0], "exit") == 0)
		builtin_exit(token, 0);
	else if (ft_strcmp(token->argv[0], "export") == 0)
		builtin_export(token, 0);
	else if (ft_strcmp(token->argv[0], "unset") == 0)
		builtin_unset(token, 0);
	else if (ft_strcmp(token->argv[0], "env") == 0)
		builtin_env(token, NULL);
	else
	{
		print_error(ERR_NO_CMD, NULL);
		quit_shell(EXIT_NORMAL_ERR);
	}
}
