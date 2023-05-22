/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 10:17:58 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/07 18:16:44 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gnl.h"

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

t_list	*make_strlst(void)
{
	t_list	*tmp;

	tmp = malloc(sizeof(t_list));
	if (tmp == NULL)
		return (NULL);
	tmp->content = malloc(sizeof(char) * BUFFER_SIZE);
	if (tmp->content == NULL)
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
		if (lst->content != NULL)
		{
			free(lst->content);
			lst->content = NULL;
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
