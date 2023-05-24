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

static void	make_num(char *ptr, int n, size_t len)
{
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
}

char	*ft_itoa(int n)
{
	char		*ptr;
	size_t		len;

	len = numlen(n);
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == 0)
		return (0);
	if (n == -2147483648)
		ft_strlcpy(ptr, "-2147483648", 12);
	else
		make_num(ptr, n, len);
	ptr[len] = 0;
	return (ptr);
}
