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

#include "fdf.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	if (n == 0)
		return (0);
	i = 0;
	while (i < n && s1[i] != 0 && s2[i] != 0)
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	if (i == n)
		i--;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
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
	sign = 1;
	while ((*str == ' ') || ('\t' <= *str && *str <= '\r'))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str == '0')
		str++;
	ret = get_num(sign, str);
	return (sign * ret);
}

int	hex_to_int(char *s)
{
	int	ret;
	int	i;

	ret = 0;
	if (*s != '0' || *(s + 1) != 'x')
		return (ret);
	s += 2;
	i = 0;
	while (i < 6)
	{
		if (*s == 0)
			return (ret);
		ret <<= 4;
		if (*s >= '0' && *s <= '9')
			ret |= (*s - '0');
		else if (*s >= 'a' && *s <= 'f')
			ret |= (*s - 'a' + 10);
		else if (*s >= 'A' && *s <= 'F')
			ret |= (*s - 'A' + 10);
		i++;
		s++;
	}
	return (ret);
}
