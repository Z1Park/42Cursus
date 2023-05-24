/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 17:40:12 by jpark2            #+#    #+#             */
/*   Updated: 2023/03/08 15:58:15 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_vec	vec(double x, double y, double z)
{
	return ((t_vec){x, y, z});
}

t_vec	vec_plus(t_vec vec1, t_vec vec2)
{
	return ((t_vec){vec1.x + vec2.x, vec1.y + vec2.y, vec1.z + vec2.z});
}

t_vec	vec_diff(t_vec vec1, t_vec vec2)
{
	return ((t_vec){vec1.x - vec2.x, vec1.y - vec2.y, vec1.z - vec2.z});
}

t_vec	vec_mul(t_vec vec, double t)
{
	return ((t_vec){vec.x * t, vec.y * t, vec.z * t});
}

t_vec	vec_div(t_vec vec, double t)
{
	if (t == 0)
		return (vec);
	return ((t_vec){vec.x / t, vec.y / t, vec.z / t});
}
