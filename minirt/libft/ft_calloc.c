/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:09:44 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/04 16:09:44 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*ptr;

	if (size != 0 && count > SIZE_MAX / size)
		return (0);
	ptr = malloc(count * size);
	if (ptr == 0)
		return (0);
	ft_memset(ptr, 0, count * size);
	return ((void *)ptr);
}
