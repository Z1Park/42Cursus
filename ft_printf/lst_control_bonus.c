/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_control_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:51:35 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/16 17:01:53 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf_bonus.h"

int	lst_add(t_list **lst, const char *s, int *len, t_ftype type)
{
	char	*tmp_s;
	t_list	*tmp_lst;

	tmp_s = ft_strdup(s, *len);
	if (tmp_s == NULL)
	{
		ft_lstclear(lst, free);
		return (0);
	}
	tmp_lst = ft_lstnew(tmp_s, *len, type);
	if (tmp_lst == NULL)
	{
		free(tmp_s);
		ft_lstclear(lst, free);
		return (0);
	}
	ft_lstadd_back(lst, tmp_lst);
	if (type != T_NONE && s[*len] != 0)
		(*len)++;
	return (1);
}

t_list	*make_lst(const char *s, t_ftype type)
{
	int		i;
	t_list	*lst;

	lst = 0;
	while (*s != 0)
	{
		i = 0;
		if (s[i] != '%')
		{
			while (s[i] != '%' && s[i] != 0)
				i++;
			type = T_NONE;
		}
		else
		{
			s++;
			while (get_ftype(s[i]) == T_NONE && s[i] != 0)
				i++;
			type = get_ftype(s[i]);
		}
		if (lst_add(&lst, s, &i, type) == 0)
			return (NULL);
		s += i;
	}
	return (lst);
}

int	lst_print(t_list *lst)
{
	while (lst != 0)
	{
		if (write(1, lst->str, lst->s_len) == -1)
			return (-1);
		lst = lst->next;
	}
	return (0);
}
