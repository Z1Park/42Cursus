/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 13:42:01 by jpark2            #+#    #+#             */
/*   Updated: 2023/03/08 15:58:18 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

int	ft_error_atoi(const char *str)
{
	long long	ret;
	int			sign;

	ret = 0;
	sign = 1;
	while ((*str == ' ') || ('\t' <= *str && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
		if (*str++ == '-')
			sign = -1;
	while ('0' <= *str && *str <= '9')
	{
		ret = ret * 10 + *str++ - '0';
		if ((sign == 1 && ret >= __INT_MAX__)
			|| (sign == -1 && ret - 1 >= __INT_MAX__))
			error_exit("Error\nparse error\n");
	}
	if (*str != 0 && *str != '\n' && (*str < '0' || *str > '9'))
		error_exit("Error\nparse error\n");
	return (sign * ret);
}

static int	get_integer_len(char *s)
{
	int	i;

	i = 0;
	while (s[i] >= '0' && s[i] <= '9')
		i++;
	if (i == 0 || (s[i] < '0' && s[i] > '9' && s[i] != '.'))
		error_exit("Error\nparse error\n");
	return (i);
}

static long	get_real_len(char *s)
{
	int	i;
	int	exp;

	i = 0;
	exp = 10;
	if (*s == '.')
		s++;
	while (s[i] >= '0' && s[i] <= '9')
	{
		i++;
		exp *= 10;
	}
	if (s[i] != 0 && s[i] != '\n' && s[i] < '0' && s[i] > '9')
		error_exit("Error\nparse error\n");
	return (exp);
}

double	ft_atod(char *s)
{
	double	num;
	int		sign;
	long	i;
	long	len;

	num = 0.0;
	sign = 1;
	if (*s == '-' || *s == '+')
		if (*s++ == '-')
			sign = -1;
	len = get_integer_len(s);
	i = 0;
	while (i++ < len)
		num = num * 10 + *s++ - '0';
	len = get_real_len(s++);
	i = 10;
	while (i < len)
	{
		num += (double)(*s++ - '0') / (double)i;
		i *= 10;
	}
	return (num * (double)sign);
}

double	degrees_to_radians(double degrees)
{
	double	theta;

	theta = degrees * M_PI / 180.0;
	if (theta <= 0 || theta > M_PI)
		error_exit("Error\ndegree setting error\n");
	return (theta);
}
