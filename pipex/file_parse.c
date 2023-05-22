/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:29:31 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/10 12:44:33 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_arg	*make_arg_var(int ac)
{
	t_arg	*args;

	args = malloc(sizeof(t_arg));
	if (args == 0)
		print_error(ERR_MALLOC, NULL);
	args->in_fd = 0;
	args->out_fd = 1;
	args->here_doc = 0;
	args->cmd_count = ac - 3;
	args->cmds = malloc(sizeof(char **) * (args->cmd_count));
	args->paths = malloc(sizeof(char *) * (args->cmd_count));
	if (args->cmds == NULL || args->paths == NULL)
		print_error(ERR_MALLOC, NULL);
	return (args);
}

static void	open_files(int ac, char **av, t_arg *args)
{
	int	in_fd;
	int	out_fd;

	if (ft_strcmp(av[1], "here_doc") == 0)
	{
		in_fd = 0;
		args->here_doc = 1;
		args->cmds[0] = here_doc_strs(av[2]);
		path_dir_check(av[ac - 1]);
		out_fd = open(av[ac - 1], O_RDWR | O_APPEND | O_CREAT, 0644);
	}
	else
	{
		in_fd = open(av[1], O_RDONLY);
		if (access(av[1], F_OK) == 0 && in_fd < 0)
			print_error(ERR_PERM_DENY, av[1]);
		path_dir_check(av[ac - 1]);
		out_fd = open(av[ac - 1], O_RDWR | O_TRUNC | O_CREAT, 0644);
	}
	if (access(av[ac - 1], F_OK) == 0 && out_fd < 0)
		print_error(ERR_PERM_DENY, av[ac - 1]);
	args->in_fd = in_fd;
	args->out_fd = out_fd;
}

static char	**find_env_path(char **env)
{
	size_t	i;
	char	**path;
	char	*tmp;

	i = 0;
	path = NULL;
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			path = ft_split(env[i] + 5, ':');
			break ;
		}
		i++;
	}
	if (path == NULL || path[0] == NULL)
		print_error(ERR_NO_CMD, NULL);
	i = 0;
	while (path[i] != NULL)
	{
		tmp = ft_strjoin(path[i], "/");
		free(path[i]);
		path[i++] = tmp;
	}
	return (path);
}

static void	find_cmd_path(t_arg *args, char **path)
{
	int		i;
	int		j;
	char	*tmp;

	i = args->here_doc;
	while (i < args->cmd_count)
	{
		j = 0;
		tmp = NULL;
		if (access(args->cmds[i][0], X_OK) == 0)
			tmp = args->cmds[i][0];
		while (path[j] != NULL && tmp == NULL)
		{
			tmp = ft_strjoin(path[j], args->cmds[i][0]);
			if (access(tmp, X_OK) == 0)
				break ;
			free(tmp);
			tmp = NULL;
			j++;
		}
		if (tmp == NULL && access(args->cmds[i][0], X_OK) != 0)
			print_error(ERR_NO_CMD, args->cmds[i][0]);
		args->paths[i] = tmp;
		i++;
	}
}

t_arg	*file_parse(int ac, char **av, char **env)
{
	t_arg	*args;
	int		i;
	char	**path;

	if (ft_strcmp("here_doc", av[1]) != 0 && access(av[1], F_OK) < 0)
		print_error(ERR_OPEN_FAIL, av[1]);
	args = make_arg_var(ac);
	open_files(ac, av, args);
	path = find_env_path(env);
	i = -1 + args->here_doc;
	while (++i < args->cmd_count)
	{
		if (ft_strchr(av[i + 2], '\'') != NULL)
			args->cmds[i] = quatation_string_parse(av[i + 2]);
		else
			args->cmds[i] = ft_split(av[i + 2], ' ');
		if (args->cmds[i] == NULL)
			print_error(ERR_MALLOC, NULL);
	}
	find_cmd_path(args, path);
	i = 0;
	while (path[i] != NULL)
		free(path[i++]);
	free(path);
	return (args);
}
