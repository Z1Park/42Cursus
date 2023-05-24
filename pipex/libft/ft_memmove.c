/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 12:44:21 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/04 12:44:21 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			i;
	unsigned char	*dest_ptr;
	unsigned char	*src_ptr;

	if (dst == 0 && src == 0)
		return (0);
	src_ptr = (unsigned char *)src;
	dest_ptr = (unsigned char *)dst;
	if (dest_ptr <= src_ptr)
		i = 0;
	else
		i = len - 1;
	while (0 <= i && i < len)
	{
		dest_ptr[i] = src_ptr[i];
		if (dest_ptr <= src_ptr)
			i++;
		else
			i--;
	}
	return (dst);
}
