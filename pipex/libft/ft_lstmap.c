/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 08:09:37 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/11 08:13:14 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*alloc_fail(t_list *created, void (*del)(void *))
{
	ft_lstclear(&created, del);
	return (0);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*created;
	t_list	*node;
	void	*tmp;

	if (f == 0 || del == 0)
		return (0);
	created = 0;
	while (lst != 0)
	{
		tmp = f(lst->content);
		if (tmp == 0)
			return (alloc_fail(created, del));
		node = ft_lstnew(tmp);
		if (node == 0)
		{
			del(tmp);
			return (alloc_fail(created, del));
		}
		ft_lstadd_back(&created, node);
		lst = lst->next;
	}
	return (created);
}
