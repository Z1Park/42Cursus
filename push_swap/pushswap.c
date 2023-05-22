/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 11:35:49 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/02 13:53:29 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

void	error_exit(void)
{
	write(1, "Error\n", 6);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	t_deque		*a_stk;

	a_stk = argument_parsing(ac, av);
	sort_deque(a_stk);
	if (a_stk->head->value > a_stk->dq_size / 2)
	{
		while (a_stk->head->value > a_stk->tail->value)
			rotate(a_stk, 'a');
	}
	else
	{
		while (a_stk->head->value > a_stk->tail->value)
			rev_rotate(a_stk, 'a');
	}
	dq_clear(&a_stk);
	return (0);
}
