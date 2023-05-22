/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:23:34 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/01 15:18:22 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	rotate(t_deque *deque, char dq)
{
	int	tmp;

	if (deque->dq_size <= 1)
		return ;
	tmp = dq_popleft(deque);
	dq_pushright(deque, tmp);
	if (dq != 0)
	{
		write(1, "r", 1);
		write(1, &dq, 1);
		write(1, "\n", 1);
	}
}

void	rev_rotate(t_deque *deque, char dq)
{
	int	tmp;

	if (deque->dq_size <= 1)
		return ;
	tmp = dq_popright(deque);
	dq_pushleft(deque, tmp);
	if (dq != 0)
	{
		write(1, "rr", 2);
		write(1, &dq, 1);
		write(1, "\n", 1);
	}
}

void	rr_rotate(t_deque *deque1, t_deque *deque2)
{
	rotate(deque1, 0);
	rotate(deque2, 0);
	write(1, "rr\n", 3);
}

void	rrr_rotate(t_deque *deque1, t_deque *deque2)
{
	rev_rotate(deque1, 0);
	rev_rotate(deque2, 0);
	write(1, "rrr\n", 4);
}
