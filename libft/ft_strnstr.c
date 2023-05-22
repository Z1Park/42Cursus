/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:43:39 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/04 15:43:39 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	idx1;
	size_t	idx2;

	if (*needle == 0)
		return ((char *)haystack);
	idx1 = 0;
	while (idx1 < len && haystack[idx1] != 0)
	{
		idx2 = 0;
		while (haystack[idx1 + idx2] == needle[idx2] && needle[idx2] != 0)
		{
			idx2++;
			if (idx1 + idx2 >= len)
				break ;
		}
		if (needle[idx2] == 0)
			return ((char *)(haystack + idx1));
		idx1++;
	}
	return (0);
}
