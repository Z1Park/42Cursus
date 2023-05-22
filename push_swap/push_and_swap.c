/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_and_swap.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:23:38 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/30 21:19:52 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	swap(t_deque *deque, char dq)
{
	int	tmp1;
	int	tmp2;

	if (deque->dq_size <= 1)
		return ;
	tmp1 = dq_popleft(deque);
	tmp2 = dq_popleft(deque);
	dq_pushleft(deque, tmp1);
	dq_pushleft(deque, tmp2);
	if (dq != 0)
	{
		write(1, "s", 1);
		write(1, &dq, 1);
		write(1, "\n", 1);
	}
}

void	push(t_deque *from, t_deque *to, char dq)
{
	int	tmp;

	if (from->dq_size <= 0)
		return ;
	tmp = dq_popleft(from);
	dq_pushleft(to, tmp);
	write(1, "p", 1);
	write(1, &dq, 1);
	write(1, "\n", 1);
}

void	ss_swap(t_deque *deque1, t_deque *deque2)
{
	swap(deque1, 0);
	swap(deque2, 0);
	write(1, "ss\n", 3);
}
