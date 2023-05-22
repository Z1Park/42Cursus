/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 10:17:58 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/03 15:27:03 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (s == NULL)
		return (0);
	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

ssize_t	ft_strnchr(const char *s, char c, size_t len)
{
	size_t	i;

	i = 0;
	while (i < len)
	{
		if (s[i] == c)
			return ((ssize_t)(i + 1));
		i++;
	}
	return (-1);
}

size_t	ft_strlcpy(char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i + 1 < n && s2[i] != '\0')
	{
		s1[i] = s2[i];
		i++;
	}
	s1[i] = '\0';
	return (i);
}

t_list	*make_strlst(void)
{
	t_list	*tmp;

	tmp = malloc(sizeof(t_list));
	if (tmp == NULL)
		return (NULL);
	tmp->str = malloc(sizeof(char) * BUFFER_SIZE);
	if (tmp->str == NULL)
	{
		free(tmp);
		return (NULL);
	}
	tmp->next = NULL;
	return (tmp);
}

void	*free_lst(t_list *lst, char **s)
{
	t_list	*tmp;

	while (lst != NULL)
	{
		tmp = lst->next;
		if (lst->str != NULL)
		{
			free(lst->str);
			lst->str = NULL;
		}
		free(lst);
		lst = tmp;
	}
	if (s != NULL)
	{
		free(*s);
		*s = NULL;
	}
	return (NULL);
}
