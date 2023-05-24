/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:15:27 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/22 10:48:57 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_routin(void *ph)
{
	t_philo	*philo;

	philo = (t_philo *)ph;
	if (philo->args->philo_cnt == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		philo->args->forks[philo->philo_num] = 1;
		pthread_mutex_unlock(philo->left_fork);
		print_message(philo->args, philo->philo_num, PRINT_TAKE_FORK);
		usleep(philo->time_to_die * 1000);
		philo_died(philo);
		return (NULL);
	}
	while (1)
	{
		if (eating(philo) != 0 || is_stop(philo->args) == 1)
			break ;
		if (sleeping(philo) != 0 || is_stop(philo->args) == 1)
			break ;
		if (thinking(philo) != 0 || is_stop(philo->args) == 1)
			break ;
	}
	return (NULL);
}

static int	destroy_mutexes(t_args *args, long long i, int flag)
{
	pthread_mutex_destroy(&(args->print));
	pthread_mutex_destroy(&(args->stop_mutex));
	if (flag == 1)
		pthread_mutex_destroy(&(args->forks_mutex[i]));
	i--;
	while (i >= 0)
	{
		pthread_mutex_destroy(&(args->forks_mutex[i]));
		pthread_mutex_destroy(&(args->philos[i].eat_cnt_mutex));
		i--;
	}
	return (-1);
}

int	philo_init(t_args *args)
{
	long long	i;

	if (pthread_mutex_init(&(args->print), NULL) != 0)
		return (-1);
	if (pthread_mutex_init(&(args->stop_mutex), NULL) != 0)
	{
		pthread_mutex_destroy(&(args->print));
		return (-1);
	}
	i = 0;
	while (i < args->philo_cnt)
	{
		if (args->philos[i].time_to_die <= 0
			|| args->philos[i].time_to_eat <= 0
			|| args->philos[i].time_to_sleep <= 0
			|| args->philos[i].must_eat < -1
			|| pthread_mutex_init(&(args->forks_mutex[i]), NULL) != 0)
			return (destroy_mutexes(args, i, 0));
		if (pthread_mutex_init(&(args->philos[i].eat_cnt_mutex), NULL) != 0)
			return (destroy_mutexes(args, i, 1));
		i++;
	}
	gettimeofday(&(args->start_time), NULL);
	return (0);
}

int	philo_start(t_args *args)
{
	long long	i;
	long long	j;

	i = 0;
	while (i < 2)
	{
		j = (i + 1) % 2;
		while (j < args->philo_cnt)
		{
			pthread_create(&(args->philos[j].pthread), NULL, \
				philo_routin, (void *)(&(args->philos[j])));
			j += 2;
		}
		usleep(SLEEP_TICK);
		i++;
	}
	return (0);
}

void	monitoring(t_args *args)
{
	long long	i;
	int			stop_flag;

	while (1)
	{
		if (is_stop(args) == 1)
			break ;
		i = 0;
		stop_flag = 1;
		while (i < args->philo_cnt)
		{
			pthread_mutex_lock(&(args->philos[i].eat_cnt_mutex));
			if (args->philos[i].must_eat == -1)
				stop_flag = 0;
			else if (args->philos[i].eat_count < args->philos[i].must_eat)
				stop_flag = 0;
			pthread_mutex_unlock(&(args->philos[i].eat_cnt_mutex));
			i++;
		}
		if (stop_flag == 1)
			stop_mutex(args);
	}
}
