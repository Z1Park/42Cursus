/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 12:35:24 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/22 10:41:20 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long long	ft_atol(const char *str)
{
	long long	ret;
	long long	sign;

	ret = 0;
	sign = 1;
	while ((*str == ' ') || ('\t' <= *str && *str <= '\r'))
		str++;
	if (*str == '+')
		str++;
	while ('0' <= *str && *str <= '9')
	{
		ret = ret * 10 + *str - '0';
		str++;
	}
	if (*str != 0 && (*str < '0' || *str > '9'))
		return (-2);
	return (sign * ret);
}

static void	set_philo_info(t_args *args, int ac, char **av, int i)
{
	args->forks[i] = 0;
	args->philos[i].left_fork = &(args->forks_mutex[i]);
	args->philos[i].right_fork = \
		&(args->forks_mutex[(i + 1) % args->philo_cnt]);
	args->philos[i].philo_num = i;
	args->philos[i].last_eat = 0;
	args->philos[i].eat_count = 0;
	args->philos[i].args = args;
	args->philos[i].time_to_die = ft_atol(av[2]);
	args->philos[i].time_to_eat = ft_atol(av[3]);
	args->philos[i].time_to_sleep = ft_atol(av[4]);
	args->philos[i].must_eat = -1;
	if (ac == 6)
		args->philos[i].must_eat = ft_atol(av[5]);
}

static int	set_philo_and_forks(t_args *args, int ac, char **av)
{
	int	i;

	args->forks_mutex = malloc(sizeof(pthread_mutex_t) * args->philo_cnt);
	if (args->forks_mutex == NULL)
		return (-1);
	args->forks = malloc(sizeof(int) * args->philo_cnt);
	if (args->forks == NULL)
	{
		free(args->forks_mutex);
		return (-1);
	}
	args->philos = malloc(sizeof(t_philo) * args->philo_cnt);
	if (args->philos == NULL)
	{
		free(args->forks_mutex);
		free(args->forks);
		return (-1);
	}
	i = 0;
	while (i < args->philo_cnt)
	{
		set_philo_info(args, ac, av, i);
		i++;
	}
	return (0);
}

t_args	*parse_arguments(int ac, char **av)
{
	t_args		*args;

	if (ac < 5 || ac > 6)
		return (NULL);
	args = malloc(sizeof(t_args));
	if (args == NULL)
		return (NULL);
	args->philo_cnt = ft_atol(av[1]);
	if (args->philo_cnt <= 0)
	{
		free(args);
		return (NULL);
	}
	args->die_print = 0;
	if (set_philo_and_forks(args, ac, av) < 0)
	{
		free(args);
		return (NULL);
	}
	args->stop = 0;
	return (args);
}
