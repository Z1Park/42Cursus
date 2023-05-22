/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/10 16:24:36 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/28 11:53:08 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	get_cur_time(t_args *args)
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

	sem_wait(args->print);
	p_time = get_cur_time(args);
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
		return (-1);
	}
	sem_post(args->print);
	return (p_time);
}

static size_t	numlen(int n)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
	else if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*ptr;
	size_t		len;

	len = numlen(n);
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == 0)
		return (NULL);
	if (n == 0)
		ptr[0] = '0';
	else if (n < 0)
	{
		n *= -1;
		ptr[0] = '-';
	}
	while (n != 0)
	{
		ptr[--len] = n % 10 + '0';
		n /= 10;
	}
	ptr[len] = 0;
	return (ptr);
}
