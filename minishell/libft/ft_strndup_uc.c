/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 16:16:27 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/04 16:16:27 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

char	*ft_strndup_uc(const char *s1, size_t len)
{
	char		*ptr;

	if (ft_strlen(s1) < len)
		len = ft_strlen(s1);
	ptr = safe_malloc_uc(sizeof(char) * (len + 1));
	ft_strlcpy(ptr, s1, len + 1);
	return (ptr);
}
