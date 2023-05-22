/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:55:30 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/04 16:55:30 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	is_in_set(char const *set, char const c)
{
	while (*set != 0)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static int	get_len(char const *s1, char const *set, int start)
{
	int		end;

	if (*s1 == 0)
		return (0);
	end = ft_strlen(s1) - 1;
	while (start < end && is_in_set(set, s1[end]) == 1)
		end--;
	return (end - start + 1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ptr;
	size_t	len;
	int		start;

	if (s1 == 0 || set == 0)
		return (0);
	if (*set == 0)
		return (ft_strdup(s1));
	start = 0;
	while (s1[start] != 0 && is_in_set(set, s1[start]) == 1)
		start++;
	len = get_len(s1, set, start);
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == 0)
		return (0);
	ft_strlcpy(ptr, s1 + start, len + 1);
	return (ptr);
}
