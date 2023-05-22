/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   greedy.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:33:04 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/01 20:26:57 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

size_t	greedy_get_count(t_deque *a, t_deque *b, size_t b_pos)
{
	size_t		count;
	size_t		a_pos;
	t_dq_node	*b_node;

	count = 1;
	b_node = find_node(b, b_pos);
	a_pos = find_position(a->head, a->tail, b_node->value);
	if (a_pos <= a->dq_size / 2 && b_pos <= b->dq_size / 2)
	{
		count += get_min(a_pos, b_pos);
		count += absolute(a_pos - b_pos);
	}
	else if (a_pos > a->dq_size / 2 && b_pos > b->dq_size / 2)
	{
		count += get_min(a->dq_size - a_pos + 1, b->dq_size - b_pos);
		count += absolute((a->dq_size - a_pos + 1) - (b->dq_size - b_pos));
	}
	else
	{
		count += get_min(a_pos, a->dq_size - a_pos);
		count += get_min(b_pos, b->dq_size - b_pos);
	}
	return (count);
}

static void	sort_with_rr(t_deque *a, t_deque *b, size_t a_pos, size_t b_pos)
{
	size_t	min;
	size_t	max;
	size_t	i;

	min = get_min(a_pos, b_pos);
	max = get_max(a_pos, b_pos);
	i = 0;
	while (i < min)
	{
		rr_rotate(a, b);
		i++;
	}
	while (i < max)
	{
		if (min == a_pos)
			rotate(b, 'b');
		else
			rotate(a, 'a');
		i++;
	}
}

static void	sort_with_rrr(t_deque *a, t_deque *b, size_t a_pos, size_t b_pos)
{
	size_t	min;
	size_t	max;
	size_t	i;

	min = get_min(a->dq_size - a_pos, b->dq_size - b_pos);
	max = get_max(a->dq_size - a_pos, b->dq_size - b_pos);
	i = 0;
	while (i < min)
	{
		rrr_rotate(a, b);
		i++;
	}
	while (i < max)
	{
		if (min == a->dq_size - a_pos)
			rev_rotate(b, 'b');
		else
			rev_rotate(a, 'a');
		i++;
	}
}

static void	sort_seperately(t_deque *a, t_deque *b, size_t a_pos, size_t b_pos)
{
	size_t	min;
	size_t	i;

	i = 0;
	min = get_min(a_pos, a->dq_size - a_pos);
	while (i < min)
	{
		if (min == a_pos)
			rotate(a, 'a');
		else
			rev_rotate(a, 'a');
		i++;
	}
	i = 0;
	min = get_min(b_pos, b->dq_size - b_pos);
	while (i < min)
	{
		if (min == b_pos)
			rotate(b, 'b');
		else
			rev_rotate(b, 'b');
		i++;
	}
}

void	greedy_move(t_deque *a, t_deque *b, size_t b_pos)
{
	size_t		a_pos;
	t_dq_node	*b_node;

	b_node = find_node(b, b_pos);
	a_pos = find_position(a->head, a->tail, b_node->value);
	if (a_pos <= a->dq_size / 2 && b_pos <= b->dq_size / 2)
		sort_with_rr(a, b, a_pos, b_pos);
	else if (a_pos > a->dq_size / 2 && b_pos > b->dq_size / 2)
		sort_with_rrr(a, b, a_pos, b_pos);
	else
		sort_seperately(a, b, a_pos, b_pos);
	push(b, a, 'a');
}
