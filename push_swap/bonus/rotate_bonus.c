/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 12:23:34 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/01 21:02:54 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap_bonus.h"

void	rotate(t_deque *deque)
{
	int	tmp;

	tmp = dq_popleft(deque);
	dq_pushright(deque, tmp);
}

void	rev_rotate(t_deque *deque)
{
	int	tmp;

	tmp = dq_popright(deque);
	dq_pushleft(deque, tmp);
}

void	rr_rotate(t_deque *deque1, t_deque *deque2)
{
	rotate(deque1);
	rotate(deque2);
}

void	rrr_rotate(t_deque *deque1, t_deque *deque2)
{
	rev_rotate(deque1);
	rev_rotate(deque2);
}
