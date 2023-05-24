/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejikim <heejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 10:54:22 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/31 13:53:28 by heejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*node;

	node = safe_malloc(sizeof(t_list));
	if (node == 0)
		return (0);
	node->content = content;
	node->next = 0;
	return (node);
}
