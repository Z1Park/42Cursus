/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:54:40 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/04 19:54:40 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	numlen(int n, char flag, size_t prec)
{
	size_t	len;

	len = 0;
	if (n < 0 || flag & (1 << 5) || flag & (1 << 6))
	{
		len++;
		prec++;
	}
	if (n == 0)
	{
		if (prec > ++len)
			return (prec);
		else
			return (len);
	}
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	if (prec > len)
		return (prec);
	else
		return (len);
}

static void	make_num(char *ptr, long long n, size_t len, char flag)
{
	size_t	sign;

	sign = 0;
	if (n < 0 || flag & (1 << 5) || flag & (1 << 6))
	{
		sign = 1;
		if (n < 0)
		{
			ptr[0] = '-';
			n *= -1;
		}
		else if (flag & (1 << 6))
			ptr[0] = '+';
		else
			ptr[0] = ' ';
	}
	if (n == 0)
		ptr[sign] = '0';
	while (n != 0)
	{
		ptr[--len] = n % 10 + '0';
		n /= 10;
	}
	while (len > sign)
		ptr[--len] = '0';
}

char	*ft_itoa(int n, char flag, size_t prec)
{
	char		*ptr;
	size_t		len;
	size_t		i;

	len = numlen(n, flag, prec);
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == 0)
		return (0);
	i = 0;
	while (i < len)
		ptr[i++] = '0';
	make_num(ptr, (long long)n, len, flag);
	ptr[len] = 0;
	return (ptr);
}
