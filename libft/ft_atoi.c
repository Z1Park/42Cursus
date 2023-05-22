/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:52:49 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/04 15:52:49 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_sign(const char **s)
{
	int	sign;

	sign = 0;
	if (sign == 0 && **s == '+')
	{
		sign = 1;
		(*s)++;
	}
	if (sign == 0 && **s == '-')
	{
		sign = -1;
		(*s)++;
	}
	if (sign == 0)
		sign = 1;
	return (sign);
}

static int	get_num(int sign, const char *str)
{
	unsigned long long	tmp;
	int					i;

	i = 0;
	tmp = 0;
	while (str[i] != 0 && i < 19)
	{
		if ('0' <= str[i] && str[i] <= '9')
			tmp = tmp * 10 + str[i] - '0';
		else
			break ;
		i++;
	}
	if ('0' <= str[i] && str[i] <= '9')
		return ((-1 * sign - 1) / 2);
	if (i == 19)
	{
		if (sign > 0 && ft_strncmp(str, "9223372036854775807", i) > 0)
			return (-1);
		else if (sign < 0 && ft_strncmp(str, "9223372036854775808", i) > 0)
			return (0);
	}
	return ((int)tmp);
}

int	ft_atoi(const char *str)
{
	int	ret;
	int	sign;

	ret = 0;
	sign = 0;
	while ((*str == ' ') || ('\t' <= *str && *str <= '\r'))
		str++;
	sign = get_sign(&str);
	while (*str == '0')
		str++;
	if ('0' <= *str && *str <= '9')
		ret = get_num(sign, str);
	return (sign * ret);
}
