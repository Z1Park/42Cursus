/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 18:22:33 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/08 19:14:40 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	count_word(char *s)
{
	int	count;

	count = 0;
	while (*s != 0)
	{
		while (*s != 0 && *s == ' ')
			s++;
		if (*s == 0)
			break ;
		count++;
		if (*s == '\'')
		{
			s++;
			while (*s != '\'' && *s != 0)
				s++;
			if (*s == 0)
				return (-1);
			else
				s++;
		}
		while (*s != '\'' && *s != ' ' && *s != 0)
			s++;
	}
	return (count);
}

static int	count_word_len(char *s)
{
	int	i;

	i = 0;
	while (*s == ' ')
		s++;
	if (*s == '\'')
	{
		s++;
		while (s[i] != '\'' && s[i] != 0)
			i++;
	}
	else
	{
		while (s[i] != '\'' && s[i] != ' ' && s[i] != 0)
			i++;
	}
	return (i);
}

static int	string_copy(char *dst, char *src, int len)
{
	int	i;

	i = 0;
	while (*src == ' ')
		src++;
	if (*src == '\'')
	{
		i++;
		src++;
	}
	ft_strlcpy(dst, src, len + 1);
	if (*src == '\'')
	{
		i++;
		src++;
	}
	return (i + len);
}

static void	*free_strs(char **s, int i)
{
	while (i >= 0)
	{
		free(s[i]);
		i--;
	}
	free(s);
	return (NULL);
}

char	**quatation_string_parse(char *str)
{
	char	**strs;
	int		count;
	int		len;
	int		i;

	count = count_word(str);
	if (count == -1)
		return (NULL);
	strs = malloc(sizeof(char *) * (count + 1));
	if (strs == NULL)
		return (NULL);
	strs[count] = NULL;
	i = 0;
	while (i < count)
	{
		len = count_word_len(str);
		strs[i] = malloc(sizeof(char) * (len + 1));
		if (strs[i] == NULL)
			return (free_strs(strs, i));
		str += string_copy(strs[i], str, len);
		i++;
	}
	return (strs);
}
