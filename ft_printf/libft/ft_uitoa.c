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

static size_t	numlen(unsigned int n, size_t prec)
{
	size_t	len;

	len = 0;
	if (n == 0)
		return (1);
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

static void	make_num(char *ptr, unsigned int n, size_t len)
{
	if (n == 0)
		ptr[0] = '0';
	while (n != 0)
	{
		ptr[--len] = n % 10 + '0';
		n /= 10;
	}
	while (len > 0)
		ptr[--len] = '0';
}

char	*ft_uitoa(unsigned int n, size_t prec)
{
	char		*ptr;
	size_t		len;

	len = numlen(n, prec);
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == 0)
		return (0);
	make_num(ptr, n, len);
	ptr[len] = 0;
	return (ptr);
}
