/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 12:35:24 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/24 18:23:28 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static long long	ft_atol(const char *str)
{
	long long	ret;
	long long	sign;

	ret = 0;
	sign = 1;
	while ((*str == ' ') || ('\t' <= *str && *str <= '\r'))
		str++;
	if (*str == '+')
	{
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		ret = ret * 10 + *str - '0';
		str++;
	}
	if (*str != 0 && (*str < '0' || *str > '9'))
		return (-2);
	return (sign * ret);
}

static int	set_params(t_args *args, int ac, char **av)
{
	args->philo_cnt = ft_atol(av[1]);
	if (args->philo_cnt <= 0)
		return (-1);
	args->time_to_die = ft_atol(av[2]);
	args->time_to_eat = ft_atol(av[3]);
	args->time_to_sleep = ft_atol(av[4]);
	args->must_eat = -1;
	if (ac == 6)
		args->must_eat = ft_atol(av[5]);
	if (args->time_to_die <= 0 || args->time_to_eat <= 0
		|| args->time_to_sleep <= 0 || args->must_eat < -1)
		return (-1);
	gettimeofday(&(args->start_time), NULL);
	args->philo->eat_count = 0;
	args->philo->last_eat = 0;
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
	args->philo = malloc(sizeof(t_philo));
	if (args->philo == NULL)
	{
		free(args);
		return (NULL);
	}
	args->pids = malloc(sizeof(pid_t) * args->philo_cnt);
	if (args->pids == NULL || set_params(args, ac, av) < 0)
	{
		free(args->philo);
		free(args);
		return (NULL);
	}
	return (args);
}
