/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 14:46:58 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/28 11:53:08 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	forks_sempost(t_args *args)
{
	sem_post(args->forks);
	sem_post(args->forks);
	return (-1);
}

int	eating(t_args *args)
{
	long long	start;

	sem_wait(args->forks);
	sem_wait(args->forks);
	print_message(args, args->philo->philo_num, PRINT_TAKE_FORK);
	print_message(args, args->philo->philo_num, PRINT_TAKE_FORK);
	start = print_message(args, args->philo->philo_num, PRINT_EATING);
	if (start < 0)
		return (forks_sempost(args));
	sem_wait(args->philo->sem_die_check);
	args->philo->last_eat = start;
	sem_post(args->philo->sem_die_check);
	usleep(args->time_to_eat * 800);
	while (get_cur_time(args) - start < args->time_to_eat)
		usleep(SLEEP_TICK);
	forks_sempost(args);
	args->philo->eat_count++;
	if (args->must_eat != -1 && args->philo->eat_count >= args->must_eat)
		exit(0);
	return (0);
}

int	sleeping(t_args *args)
{
	long long	start;
	long long	time;

	start = print_message(args, args->philo->philo_num, PRINT_SLEEPING);
	if (start < 0)
		return (-1);
	time = get_cur_time(args);
	while (time - start < args->time_to_sleep)
	{
		usleep(SLEEP_TICK);
		time = get_cur_time(args);
	}
	return (0);
}

int	thinking(t_args *args)
{
	if (print_message(args, args->philo->philo_num, PRINT_THINKING) < 0)
		return (-1);
	return (0);
}
