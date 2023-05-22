/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_sorting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 10:23:52 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/02 13:53:16 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static void	sort_three_args(t_deque *a)
{
	if (a->head->value < a->head->next->value)
	{
		if (a->head->next->value > a->tail->value)
		{
			rev_rotate(a, 'a');
			if (a->head->value > a->head->next->value)
				swap(a, 'a');
		}
	}
	else
	{
		if (a->head->next->value > a->tail->value)
		{
			rotate(a, 'a');
			swap(a, 'a');
		}
		else
		{
			if (a->head->value < a->tail->value)
				swap(a, 'a');
			else
				rotate(a, 'a');
		}
	}
}

static void	sort_few_args(t_deque *a, t_deque *b, int count)
{
	size_t		i;
	size_t		min_i;

	min_i = find_min_node(a->head);
	i = 0;
	if (min_i <= a->dq_size / 2)
	{
		while (i++ < min_i)
			rotate(a, 'a');
	}
	else
	{
		while (i++ < a->dq_size - min_i)
			rev_rotate(a, 'a');
	}
	push(a, b, 'b');
	if (count > 4)
		sort_few_args(a, b, count - 1);
	else
		sort_three_args(a);
	push(b, a, 'a');
}

static void	arrange_three_div(t_deque *a, t_deque *b)
{
	size_t	max;
	size_t	i;

	i = 0;
	max = a->dq_size;
	while (i++ < max && a->dq_size > 3)
	{
		if (a->head->value <= (long long)max / 3)
			push(a, b, 'b');
		else if (a->head->value <= (long long)max * 2 / 3)
		{
			push(a, b, 'b');
			if (a->head->value > (long long)max * 2 / 3)
			{
				rr_rotate(a, b);
				i++;
			}
			else
				rotate(b, 'b');
		}
		else
			rotate(a, 'a');
	}
	while (a->dq_size > 3)
		push(a, b, 'b');
}

static void	select_and_move(t_deque *a, t_deque *b)
{
	size_t	min;
	size_t	tmp;
	size_t	i;
	size_t	min_i;

	i = 0;
	min = SIZE_MAX - 1;
	while (i < b->dq_size)
	{
		tmp = greedy_get_count(a, b, i);
		if (tmp < min)
		{
			min = tmp;
			min_i = i;
		}
		i++;
	}
	greedy_move(a, b, min_i);
}

void	sort_deque(t_deque *a_stk)
{
	t_deque	*b_stk;

	b_stk = create_deque();
	if (a_stk->dq_size == 2 && dq_is_sorted(a_stk) == -1)
		swap(a_stk, 'a');
	else if (a_stk->dq_size == 3)
		sort_three_args(a_stk);
	else if (a_stk->dq_size <= 5)
		sort_few_args(a_stk, b_stk, a_stk->dq_size);
	else
	{
		arrange_three_div(a_stk, b_stk);
		if (a_stk->dq_size == 3)
			sort_three_args(a_stk);
		while (b_stk->dq_size != 0)
			select_and_move(a_stk, b_stk);
	}
	dq_clear(&b_stk);
}
