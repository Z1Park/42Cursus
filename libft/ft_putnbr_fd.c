/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 21:44:41 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/04 21:44:41 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
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
	long long	num;

	num = n;
	if (n == 0)
		ptr[0] = '0';
	else if (n < 0)
	{
		num *= -1;
		ptr[0] = '-';
	}
	while (num != 0)
	{
		ptr[--len] = num % 10 + '0';
		num /= 10;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	trans[12];
	size_t	len;

	if (fd < 0)
		return ;
	len = numlen(n);
	ft_memset(trans, 0, 12);
	make_num(trans, n, len);
	write(fd, trans, ft_strlen(trans));
}
