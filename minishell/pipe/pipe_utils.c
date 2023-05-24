/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 13:59:04 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/07 10:10:57 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_cmd_count(t_pipe *pipes)
{
	int	count;

	count = 0;
	while (pipes != NULL)
	{
		count++;
		pipes = pipes->next;
	}
	return (count);
}

char	**get_cmd_paths(void)
{
	size_t	i;
	char	**path;
	char	*tmp;

	path = NULL;
	i = 0;
	while (g_sys.p_env[i] != NULL)
	{
		if (ft_strncmp(g_sys.p_env[i], "PATH=", 5) == 0)
		{
			path = ft_split(g_sys.p_env[i] + 5, ':');
			break ;
		}
		i++;
	}
	i = 0;
	while (path != NULL && path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		safe_free(path[i]);
		path[i++] = tmp;
	}
	return (path);
}

char	*find_cmd_path(char **path, t_pipe *pipe)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	if (is_builtin(pipe->argv[0]) == TRUE || access(pipe->argv[0], X_OK) == 0)
		tmp = pipe->argv[0];
	i = 0;
	while (path[i] != NULL && tmp == NULL)
	{
		tmp = ft_strjoin(path[i], pipe->argv[0]);
		if (access(tmp, X_OK) == 0)
			break ;
		safe_free(tmp);
		tmp = NULL;
		i++;
	}
	if (tmp == NULL)
	{
		if (access(pipe->argv[0], F_OK) != 0)
			print_error(ERR_NO_CMD, pipe->argv[0]);
		else if (access(pipe->argv[0], X_OK) != 0)
			print_error(ERR_AUTH_FAIL, pipe->argv[0]);
	}
	return (tmp);
}

char	**token_to_cmd_path(t_pipe *pipes, int cmd_count)
{
	int		i;
	char	**path;
	char	**cmd_path;

	path = get_cmd_paths();
	cmd_path = safe_malloc(sizeof(char *) * cmd_count);
	i = 0;
	while (i < cmd_count && pipes != NULL)
	{
		if (pipes->argc != 0 && path != NULL)
			cmd_path[i] = find_cmd_path(path, pipes);
		else
		{
			if (pipes->argc != 0 && access(pipes->argv[0], X_OK) != 0
				&& is_builtin(pipes->argv[0]) != TRUE)
				print_error(ERR_NO_CMD, pipes->argv[0]);
			cmd_path[i] = NULL;
		}
		pipes = pipes->next;
		i++;
	}
	if (path != NULL)
		free_splited(path, get_split_size(path));
	return (cmd_path);
}

int	check_need_fork(t_token *tokens)
{
	size_t		i;
	const char	*builtins_name[] = {"exit", "cd", "export", "unset"};
	static void	(*builtin_fp[])(t_pipe *, int) = {builtin_exit, builtin_cd, \
		builtin_export, builtin_unset};

	if (tokens->pipes->next != NULL || tokens->pipes->argc == 0
		|| tokens->pipes->result != TOKEN_SUCCESS)
		return (0);
	i = 0;
	while (i < 4)
	{
		if (ft_strcmp(tokens->pipes->argv[0], builtins_name[i]) == 0)
		{
			builtin_fp[i](tokens->pipes, 1);
			redirect_in_restore(tokens);
			redirect_out_restore(tokens);
			return (1);
		}
		i++;
	}
	return (0);
}
