/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 11:33:52 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/24 18:15:12 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	unlink_and_free(t_args *args)
{
	sem_close(args->print);
	sem_close(args->forks);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_FORKS);
	free(args->philo);
	free(args->pids);
	free(args);
	return (1);
}

int	main(int ac, char **av)
{
	t_args	*args;
	pid_t	pid;

	args = parse_arguments(ac, av);
	if (args == NULL)
		return (1);
	if (philo_init(args) < 0)
		return (unlink_and_free(args));
	pid = philo_start(args);
	if (pid >= 0)
		monitoring(args, pid);
	else
		return (unlink_and_free(args));
	unlink_and_free(args);
	return (0);
}
