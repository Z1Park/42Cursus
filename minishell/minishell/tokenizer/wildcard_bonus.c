/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 13:07:55 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/06 21:24:20 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static char	**alloc_match_files(char *wildcard, char **cwd_files)
{
	size_t	i;
	size_t	count;
	char	**match_files;

	i = 0;
	count = 0;
	while (cwd_files[i] != NULL)
	{
		if (wildcard_strcmp(wildcard, wildcard, cwd_files[i]) == 0)
			count++;
		i++;
	}
	match_files = safe_malloc(sizeof(char *) * (count + 1));
	return (match_files);
}

char	**find_wildcard_files(char *wildcard)
{
	char	**cwd_files;
	char	**match_files;
	size_t	i;
	size_t	j;

	cwd_files = get_cwd_files();
	match_files = alloc_match_files(wildcard, cwd_files);
	i = 0;
	j = 0;
	while (cwd_files[i] != NULL)
	{
		if (wildcard_strcmp(wildcard, wildcard, cwd_files[i]) == 0)
		{
			match_files[j] = remove_backslash(ft_strdup(cwd_files[i]));
			j++;
		}
		i++;
	}
	match_files[j] = NULL;
	return (match_files);
}

char	*remove_backslash(char *str)
{
	char	*tmp;
	char	*res;
	int		i;

	i = 0;
	tmp = str;
	while (*tmp != '\0')
	{
		if (*tmp == '\\' && *(tmp + 1) == '*')
			tmp++;
		i++;
		tmp++;
	}
	res = safe_malloc(sizeof(char) * (i + 1));
	i = 0;
	while (*str != '\0')
	{
		if (*str == '\\' && *(str + 1) == '*')
			str++;
		res[i++] = *(str++);
	}
	res[i] = '\0';
	return (res);
}
