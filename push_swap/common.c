/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 13:22:29 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/01 13:52:36 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

long long	get_min(long long a, long long b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

long long	get_max(long long a, long long b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

long long	absolute(long long n)
{
	if (n < 0)
		return (-n);
	else
		return (n);
}

size_t	find_min_node(t_dq_node *node)
{
	size_t		i;
	size_t		min_i;
	long long	min;

	min = 2147483648;
	i = 0;
	min_i = 0;
	while (node != NULL)
	{
		if (min > node->value)
		{
			min = node->value;
			min_i = i;
		}
		i++;
		node = node->next;
	}
	return (min_i);
}

size_t	find_max_node(t_dq_node *node)
{
	size_t		i;
	size_t		max_i;
	long long	max;

	max = -2147483649;
	i = 0;
	max_i = 0;
	while (node != NULL)
	{
		if (max < node->value)
		{
			max = node->value;
			max_i = i;
		}
		i++;
		node = node->next;
	}
	return (max_i);
}
