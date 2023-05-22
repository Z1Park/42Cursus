/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 08:09:13 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/11 08:13:07 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (lst == 0 || *lst == 0 || del == 0)
		return ;
	tmp = *lst;
	while (tmp != 0)
	{
		*lst = tmp->next;
		ft_lstdelone(tmp, del);
		tmp = *lst;
	}
}
