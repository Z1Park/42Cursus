/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork_ctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 10:55:43 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/24 12:19:05 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	fork_lock(t_philo *philo, t_args *args)
{
	int	res;

	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	if (args->forks[(philo->philo_num + 1) % args->philo_cnt] == 0
		&& args->forks[philo->philo_num] == 0)
	{
		args->forks[(philo->philo_num + 1) % args->philo_cnt] = 2;
		args->forks[philo->philo_num] = 1;
		print_message(philo->args, philo->philo_num, PRINT_TAKE_FORK);
		print_message(philo->args, philo->philo_num, PRINT_TAKE_FORK);
	}
	if (args->forks[(philo->philo_num + 1) % args->philo_cnt] == 2
		&& args->forks[philo->philo_num] == 1)
		res = 1;
	else
		res = 0;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (res);
}

int	fork_unlock(t_philo *philo, t_args *args)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(philo->left_fork);
	if (args->forks[(philo->philo_num + 1) % args->philo_cnt] == 2)
		args->forks[(philo->philo_num + 1) % args->philo_cnt] = 0;
	if (args->forks[philo->philo_num] == 1)
		args->forks[philo->philo_num] = 0;
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (-1);
}
