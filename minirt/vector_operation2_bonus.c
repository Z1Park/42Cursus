/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_operation2_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:11:38 by mingkang          #+#    #+#             */
/*   Updated: 2023/03/08 15:58:16 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_vec	vec_mul2(t_vec v1, t_vec v2)
{
	return ((t_vec){v1.x * v2.x, v1.y * v2.y, v1.z * v2.z});
}

t_vec	vec_neg(t_vec v1)
{
	return (vec(-v1.x, -v1.y, -v1.z));
}

t_vec	vec_reflect(t_vec v, t_vec normal)
{
	t_vec	out;

	out = vec_diff(v, vec_mul(normal, vec_dot(v, normal) * 2));
	return (out);
}

t_vec	vec_refract(t_vec unit_vec, t_vec normal, double eta_ratio)
{
	double	cos_theta;
	t_vec	r_perp;
	t_vec	r_parallel;

	cos_theta = fmin(vec_dot(vec_neg(unit_vec), normal), 1.0);
	r_perp = vec_mul(vec_plus(unit_vec, vec_mul(normal, cos_theta)), eta_ratio);
	r_parallel = vec_mul(normal, -sqrt((fabs(1.0 - vec_dot(r_perp, r_perp)))));
	return (vec_plus(r_perp, r_parallel));
}

int	vec_cmp(t_vec v1, t_vec v2)
{
	if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z)
		return (0);
	return (1);
}
