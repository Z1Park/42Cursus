/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 15:33:15 by mingkang          #+#    #+#             */
/*   Updated: 2023/03/08 15:58:25 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

double	rand_double(void)
{
	return ((double)rand() / (double)RAND_MAX);
}

double	rand_minmax(double min, double max)
{
	return (min + (max - min) * rand_double());
}

t_vec	rand_in_unit_sphere(void)
{
	t_vec	p;

	while (1)
	{
		p = vec(rand_minmax(-1, 1), rand_minmax(-1, 1), rand_minmax(-1, 1));
		if (vec_scalar(p) >= 1)
			continue ;
		return (p);
	}
}

t_vec	random_unit_vec(void)
{
	return (vec_unit(rand_in_unit_sphere()));
}

t_vec	rand_in_unit_disk(void)
{
	t_vec	p;

	while (1)
	{
		p = vec(rand_minmax(-1, 1), rand_minmax(-1, 1), 0);
		if (vec_dot(p, p) >= 1)
			continue ;
		return (p);
	}
}
