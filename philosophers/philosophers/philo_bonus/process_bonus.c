/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:24:18 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/28 11:55:16 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*philo_routin(void *arguments)
{
	t_args	*args;

	args = (t_args *)arguments;
	if (args->philo_cnt == 1)
	{
		sem_wait(args->forks);
		print_message(args, args->philo->philo_num, PRINT_TAKE_FORK);
		sem_wait(args->forks);
		print_message(args, args->philo->philo_num, PRINT_TAKE_FORK);
	}
	while (1)
	{
		if (eating(args) != 0)
			break ;
		if (sleeping(args) != 0)
			break ;
		if (thinking(args) != 0)
			break ;
	}
	return (NULL);
}

static int	unlink_and_close(t_args *args, int idx)
{
	if (idx >= 1)
	{
		sem_close(args->print);
		sem_unlink(SEM_PRINT);
	}
	if (idx >= 2)
	{
		sem_close(args->forks);
		sem_unlink(SEM_FORKS);
	}
	return (-1);
}

int	philo_init(t_args *args)
{
	int		i;
	char	*tmp;

	sem_unlink(SEM_PRINT);
	args->print = sem_open(SEM_PRINT, O_CREAT, 644, 1);
	if (args->print == SEM_FAILED)
		return (unlink_and_close(args, 1));
	sem_unlink(SEM_FORKS);
	args->forks = sem_open(SEM_FORKS, O_CREAT, 644, args->philo_cnt);
	if (args->forks == SEM_FAILED)
		return (unlink_and_close(args, 2));
	i = 0;
	while (i < args->philo_cnt)
	{
		tmp = ft_itoa(i);
		sem_unlink(tmp);
		args->philo->sem_die_check = sem_open(tmp, O_CREAT, 644, 1);
		free(tmp);
		if (args->philo->sem_die_check == SEM_FAILED)
			return (unlink_and_close(args, 3));
		i++;
	}
	return (0);
}

pid_t	philo_start(t_args *args)
{
	long long	i;
	long long	j;
	pid_t		pid;

	i = -1;
	while (++i < 2)
	{
		j = (i + 1) % 2;
		while (j < args->philo_cnt)
		{
			pid = fork();
			if (pid == 0)
			{
				args->philo->philo_num = j;
				pthread_create(&(args->philo->pthread), NULL, \
					philo_routin, (void *)(args));
				return (pid);
			}
			else
				args->pids[j] = pid;
			j += 2;
		}
		usleep(SLEEP_TICK);
	}
	return (pid);
}

void	monitoring(t_args *args, pid_t pid)
{
	long long	i;

	if (pid == 0)
	{
		while (1)
		{
			sem_wait(args->philo->sem_die_check);
			if (get_cur_time(args) - args->philo->last_eat > args->time_to_die)
				break ;
			sem_post(args->philo->sem_die_check);
		}
		print_message(args, args->philo->philo_num, PRINT_DIED);
		exit(0);
	}
	if (args->must_eat == -1)
		waitpid(-1, NULL, 0);
	else
	{
		i = 0;
		while (i < args->philo_cnt)
			waitpid(args->pids[i++], NULL, 0);
	}
	i = 0;
	while (i < args->philo_cnt)
		kill(args->pids[i++], SIGKILL);
}
