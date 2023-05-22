/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 10:24:06 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/10 10:03:58 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	args_clear(t_arg *args)
{
	int	i;
	int	j;

	i = 0;
	while (i < args->cmd_count)
	{
		j = 0;
		while (args->cmds[i][j] != NULL)
			free(args->cmds[i][j++]);
		free(args->cmds[i++]);
	}
	free(args->cmds);
	i = 0;
	while (i < args->cmd_count)
		free(args->paths[i++]);
	free(args->paths);
	free(args);
}

int	main(int ac, char **av, char **env)
{
	t_arg	*args;
	char	*tmp;
	int		status;

	if (ac <= 4)
		print_error(ERR_PARAM, NULL);
	args = file_parse(ac, av, env);
	if (args->here_doc == 1)
	{
		tmp = ft_strjoin(args->cmds[0][0], "\n");
		free(args->cmds[0][0]);
		args->cmds[0][0] = tmp;
		status = here_doc(args, env);
	}
	else
		status = pipe_line(args, env);
	args_clear(args);
	return (status);
}
