/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 20:32:43 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/04 20:32:43 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	len;
	size_t	i;
	char	*ptr;

	if (s == 0 || f == 0)
		return (0);
	len = ft_strlen(s);
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == 0)
		return ((char *)0);
	ptr[len] = 0;
	i = 0;
	while (i < len)
	{
		ptr[i] = f(i, s[i]);
		i++;
	}
	return (ptr);
}
