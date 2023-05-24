/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:28:17 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/04 16:28:17 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	s_len;

	if (s == 0)
		return (0);
	s_len = ft_strlen(s);
	if (s_len == 0 || s_len <= start)
		len = 0;
	else if (s_len < start + len)
		len = s_len - start;
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == 0)
		return (0);
	if (len != 0 && s_len > start)
		s += start;
	ft_strlcpy(ptr, s, len + 1);
	return (ptr);
}
