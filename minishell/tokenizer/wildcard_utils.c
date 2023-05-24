/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 19:49:11 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/06 21:40:38 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "minishell.h"

static size_t	get_cwd_files_count(char *curr_path)
{
	struct dirent	*files;
	size_t			count;
	DIR				*dirp;

	dirp = opendir(curr_path);
	if (dirp == NULL)
		print_error(ERR_OPENDIR, NULL);
	count = 0;
	while (1)
	{
		files = readdir(dirp);
		if (files == NULL)
			break ;
		count++;
		files = NULL;
	}
	closedir(dirp);
	return (count);
}

char	**get_cwd_files(void)
{
	char	**files;
	size_t	files_cnt;
	size_t	i;
	DIR		*dirp;
	char	*curr_path;

	curr_path = getcwd(NULL, BUF_MAX);
	if (curr_path == NULL)
		print_error(ERR_GET_CWD, NULL);
	files_cnt = get_cwd_files_count(curr_path);
	files = safe_malloc(sizeof(char *) * (files_cnt + 1));
	dirp = opendir(curr_path);
	if (dirp == NULL)
		print_error(ERR_OPENDIR, NULL);
	i = 0;
	while (i < files_cnt)
		files[i++] = ft_strdup(readdir(dirp)->d_name);
	files[i] = NULL;
	safe_free(curr_path);
	closedir(dirp);
	return (files);
}

static int	wildcard_str_cmp(char **wildcard, char **str)
{
	size_t	i;

	while (**wildcard == '*')
		(*wildcard)++;
	if (**wildcard == '\0')
		return (1);
	i = 0;
	while ((*wildcard)[i] != '*' && (*wildcard)[i] != '\0')
		i++;
	while (**str != '\0' && ft_strncmp(*str, *wildcard, i) != 0)
		(*str)++;
	if (**str == '\0')
		return (-1);
	*str += i;
	*wildcard += i;
	return (1);
}

void	skip_char_asterisk(char **str, char **wildcard)
{
	if (**wildcard == '\\' && *(*wildcard + 1) == '*')
	{
		(*wildcard)++;
		if (**str == '*')
		{
			(*str)++;
			(*wildcard)++;
		}
	}
}

int	wildcard_strcmp(char *wildcard, char *start, char *str)
{
	int		flag;

	while (*wildcard != '\0')
	{
		if ((wildcard == start || *(wildcard - 1) != '\\') && *wildcard == '*')
		{
			flag = wildcard_str_cmp(&wildcard, &str);
			if (flag <= 0)
				return (flag);
		}
		else
		{
			if (*wildcard != *str)
				return (-1);
			while (*wildcard != '\0' && *str != '\0'
				&& *wildcard != '*' && *wildcard == *str)
			{
				wildcard++;
				str++;
			}
			skip_char_asterisk(&str, &wildcard);
		}
	}
	return (0);
}
