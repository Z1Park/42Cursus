/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 11:33:52 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/22 10:41:55 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_and_free(t_args *args)
{
	long long	i;

	pthread_mutex_destroy(&(args->print));
	pthread_mutex_destroy(&(args->stop_mutex));
	i = 0;
	while (i < args->philo_cnt)
	{
		pthread_mutex_destroy(&(args->forks_mutex[i]));
		pthread_mutex_destroy(&(args->philos[i].eat_cnt_mutex));
		i++;
	}
	free(args->philos);
	free(args->forks_mutex);
	free(args->forks);
	free(args);
	return (1);
}

int	main(int ac, char **av)
{
	t_args	*args;
	int		i;

	args = parse_arguments(ac, av);
	if (args == NULL)
		return (1);
	if (philo_init(args) < 0)
		return (destroy_and_free(args));
	if (philo_start(args) < 0)
		return (destroy_and_free(args));
	monitoring(args);
	i = 0;
	while (i < args->philo_cnt)
		pthread_join(args->philos[i++].pthread, NULL);
	destroy_and_free(args);
	return (0);
}
