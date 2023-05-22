/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 19:01:58 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/04 19:01:58 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	word_cnt;

	word_cnt = 0;
	while (*s != 0)
	{
		while (*s == c)
			s++;
		if (*s == 0)
			break ;
		word_cnt++;
		while (*s != c && *s != 0)
			s++;
	}
	return (word_cnt);
}

static size_t	word_len(char const *s, char c)
{
	size_t	len;

	len = 0;
	while (*s != c && *s != 0)
	{
		len++;
		s++;
	}
	return (len);
}

static int	word_malloc(char **ptr, size_t i, size_t len)
{
	ptr[i] = malloc(sizeof(char) * (len + 1));
	if (ptr[i] == 0)
	{
		while (i-- > 0)
			free(ptr[i]);
		free(ptr);
		return (0);
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**ptr;
	size_t	i;
	size_t	word_cnt;
	size_t	len;

	if (s == 0)
		return (0);
	word_cnt = count_words(s, c);
	ptr = malloc(sizeof(char *) * (word_cnt + 1));
	if (ptr == 0)
		return (0);
	ptr[word_cnt] = 0;
	i = 0;
	while (i < word_cnt)
	{
		while (*s == c)
			s++;
		len = word_len(s, c);
		if (word_malloc(ptr, i, len) == 0)
			return (0);
		ft_strlcpy(ptr[i], s, len + 1);
		s += len;
		i++;
	}
	return (ptr);
}
