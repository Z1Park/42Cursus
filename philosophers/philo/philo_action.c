/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:46:58 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/28 11:58:25 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	increase_eat_count(t_philo *philo)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&(philo->eat_cnt_mutex));
	philo->eat_count++;
	if (philo->must_eat != -1
		&& philo->eat_count >= philo->must_eat)
		ret = -1;
	pthread_mutex_unlock(&(philo->eat_cnt_mutex));
	return (ret);
}

int	eating(t_philo *philo)
{
	long long	start;

	while (fork_lock(philo, philo->args) == 0)
	{
		if (get_curr_time(philo->args) - philo->last_eat > philo->time_to_die)
			return (philo_died(philo));
		usleep(SLEEP_TICK);
	}
	if (is_stop(philo->args) == 1)
		return (fork_unlock(philo, philo->args));
	if (get_curr_time(philo->args) - philo->last_eat > philo->time_to_die)
		return (fork_unlock(philo, philo->args) + philo_died(philo));
	start = print_message(philo->args, philo->philo_num, PRINT_EATING);
	if (start < 0)
		return (fork_unlock(philo, philo->args));
	usleep(philo->time_to_eat * 800);
	while (get_curr_time(philo->args) - start < philo->time_to_eat)
		usleep(SLEEP_TICK);
	fork_unlock(philo, philo->args);
	philo->last_eat = start;
	if (increase_eat_count(philo) < 0)
		return (-1);
	return (0);
}

int	sleeping(t_philo *philo)
{
	long long	start;
	long long	time;

	start = print_message(philo->args, philo->philo_num, PRINT_SLEEPING);
	if (start < 0)
		return (-1);
	if (is_stop(philo->args) == 1)
		return (-1);
	time = get_curr_time(philo->args);
	while (time - start < philo->time_to_sleep)
	{
		if (time - philo->last_eat > philo->time_to_die)
			return (philo_died(philo));
		usleep(SLEEP_TICK);
		time = get_curr_time(philo->args);
	}
	if (is_stop(philo->args) == 1)
		return (-1);
	return (0);
}

int	thinking(t_philo *philo)
{
	if (print_message(philo->args, philo->philo_num, PRINT_THINKING) < 0)
		return (-1);
	return (0);
}
