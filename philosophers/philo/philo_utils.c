/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 16:24:36 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/22 10:50:18 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_curr_time(t_args *args)
{
	struct timeval	curr_time;
	long long		time;

	gettimeofday(&curr_time, NULL);
	time = (curr_time.tv_sec - args->start_time.tv_sec) * 1000 + \
		(curr_time.tv_usec - args->start_time.tv_usec) / 1000;
	return (time);
}

long long	print_message(t_args *args, long long philo_num, t_print prt)
{
	long long	p_time;

	pthread_mutex_lock(&(args->print));
	p_time = get_curr_time(args);
	if (is_stop(args) == 1 && args->die_print == 1)
	{
		pthread_mutex_unlock(&(args->print));
		return (-1);
	}
	if (prt == PRINT_TAKE_FORK)
		printf("%lld %lld has taken a fork\n", p_time, philo_num + 1);
	else if (prt == PRINT_EATING)
		printf("%lld %lld is eating\n", p_time, philo_num + 1);
	else if (prt == PRINT_SLEEPING)
		printf("%lld %lld is sleeping\n", p_time, philo_num + 1);
	else if (prt == PRINT_THINKING)
		printf("%lld %lld is thinking\n", p_time, philo_num + 1);
	else
	{
		printf("%lld %lld is died\n", p_time, philo_num + 1);
		args->die_print = 1;
	}
	pthread_mutex_unlock(&(args->print));
	return (p_time);
}

int	philo_died(t_philo *philo)
{
	stop_mutex(philo->args);
	print_message(philo->args, philo->philo_num, PRINT_DIED);
	return (-1);
}

void	stop_mutex(t_args *args)
{
	pthread_mutex_lock(&(args->stop_mutex));
	args->stop = 1;
	pthread_mutex_unlock(&(args->stop_mutex));
}

int	is_stop(t_args *args)
{
	int	ret;

	pthread_mutex_lock(&(args->stop_mutex));
	ret = args->stop;
	pthread_mutex_unlock(&(args->stop_mutex));
	return (ret);
}
