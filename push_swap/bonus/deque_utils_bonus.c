/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 21:25:16 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/01 20:49:12 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap_bonus.h"

int	dq_is_sorted(t_deque *deque)
{
	t_dq_node	*curr;

	curr = deque->head;
	while (curr->next != NULL)
	{
		if (curr->value > curr->next->value)
			return (-1);
		curr = curr->next;
	}
	return (0);
}

void	dq_clear(t_deque **deque)
{
	while (dq_popleft(*deque) != -1)
		;
	free(*deque);
	*deque = NULL;
}
