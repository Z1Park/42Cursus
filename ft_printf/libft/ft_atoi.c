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

int	ft_atoi(const char *str)
{
	int	ret;
	int	sign;

	ret = 0;
	sign = 0;
	while ((*str == ' ') || ('\t' <= *str && *str <= '\r'))
		str++;
	if (sign == 0 && *str == '+')
	{
		sign = 1;
		str++;
	}
	if (sign == 0 && *str == '-')
	{
		sign = -1;
		str++;
	}
	if (sign == 0)
		sign = 1;
	while ('0' <= *str && *str <= '9')
	{
		ret = ret * 10 + *str - '0';
		str++;
	}
	return (sign * ret);
}
