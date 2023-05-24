/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 21:25:16 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/01 17:59:10 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

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

t_dq_node	*find_node(t_deque *deque, size_t pos)
{
	t_dq_node	*node;
	size_t		i;

	i = 0;
	if (pos <= deque->dq_size / 2)
	{
		node = deque->head;
		while (i < pos)
		{
			node = node->next;
			i++;
		}
	}
	else
	{
		node = deque->tail;
		while (deque->dq_size - 1 - i > pos)
		{
			node = node->prev;
			i++;
		}
	}
	return (node);
}

size_t	find_position(t_dq_node *node, t_dq_node *last, long long value)
{
	size_t	i;

	i = 0;
	if (node == NULL || (last->value < value && node->value > value))
		return (0);
	while (node->next != NULL)
	{
		if (node->value < value && node->next->value > value)
			break ;
		if (node->value > node->next->value
			&& (node->value < value || node->next->value > value))
			return (i + 1);
		node = node->next;
		i++;
	}
	if (node->value < value)
		i++;
	if (node == last && node->value > value)
		return (0);
	return (i);
}
