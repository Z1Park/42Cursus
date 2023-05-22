/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_and_swap_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:23:38 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/01 21:02:26 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap_bonus.h"

void	swap(t_deque *deque)
{
	int	tmp1;
	int	tmp2;

	if (deque->dq_size <= 1)
		return ;
	tmp1 = dq_popleft(deque);
	tmp2 = dq_popleft(deque);
	dq_pushleft(deque, tmp1);
	dq_pushleft(deque, tmp2);
}

void	push(t_deque *from, t_deque *to)
{
	int	tmp;

	if (from->dq_size <= 0)
		return ;
	tmp = dq_popleft(from);
	dq_pushleft(to, tmp);
}

void	ss_swap(t_deque *deque1, t_deque *deque2)
{
	swap(deque1);
	swap(deque2);
}
