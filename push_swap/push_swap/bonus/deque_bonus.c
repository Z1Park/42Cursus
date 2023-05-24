/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 09:51:11 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/01 17:30:51 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap_bonus.h"

void	dq_pushleft(t_deque *deque, long long value)
{
	t_dq_node	*new_node;

	new_node = malloc(sizeof(t_dq_node));
	if (new_node == NULL)
		error_exit();
	new_node->value = value;
	new_node->prev = NULL;
	new_node->next = deque->head;
	if (deque->head != NULL)
		deque->head->prev = new_node;
	deque->head = new_node;
	if (deque->tail == NULL)
		deque->tail = new_node;
	deque->dq_size += 1;
}

void	dq_pushright(t_deque *deque, long long value)
{
	t_dq_node	*new_node;

	new_node = malloc(sizeof(t_dq_node));
	if (new_node == NULL)
		error_exit();
	new_node->value = value;
	new_node->prev = deque->tail;
	if (deque->tail != NULL)
		deque->tail->next = new_node;
	new_node->next = NULL;
	deque->tail = new_node;
	if (deque->head == NULL)
		deque->head = new_node;
	deque->dq_size += 1;
}

long long	dq_popleft(t_deque *deque)
{
	t_dq_node	*tmp;
	int			value;

	if (deque->head == NULL)
		return (-1);
	tmp = deque->head;
	deque->head = deque->head->next;
	if (deque->head != NULL)
		deque->head->prev = NULL;
	deque->dq_size -= 1;
	if (deque->dq_size == 0)
		deque->tail = NULL;
	value = tmp->value;
	free(tmp);
	return (value);
}

long long	dq_popright(t_deque *deque)
{
	t_dq_node	*tmp;
	int			value;

	if (deque->tail == NULL)
		return (-1);
	tmp = deque->tail;
	deque->tail = deque->tail->prev;
	if (deque->tail != NULL)
		deque->tail->next = NULL;
	deque->dq_size -= 1;
	if (deque->dq_size == 0)
		deque->head = NULL;
	value = tmp->value;
	free(tmp);
	return (value);
}

t_deque	*create_deque(void)
{
	t_deque	*deque;

	deque = malloc(sizeof(t_deque));
	if (deque == NULL)
		error_exit();
	deque->head = NULL;
	deque->tail = NULL;
	deque->dq_size = 0;
	return (deque);
}
