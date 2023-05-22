/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingkang <mingkang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:13:49 by jpark2            #+#    #+#             */
/*   Updated: 2023/03/01 16:13:48 by mingkang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vec	vec_unit(t_vec vec)
{
	double	len;

	len = sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
	if (len == 0)
		return (vec);
	return ((t_vec){vec.x / len, vec.y / len, vec.z / len});
}

double	vec_scalar(t_vec vec)
{
	return (sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z));
}

double	vec_dot(t_vec vec1, t_vec vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y + vec1.z * vec2.z);
}

t_vec	vec_cross(t_vec v1, t_vec v2)
{
	t_vec	out;

	out.x = v1.y * v2.z - v1.z * v2.y;
	out.y = v1.z * v2.x - v1.x * v2.z;
	out.z = v1.x * v2.y - v1.y * v2.x;
	return (out);
}

double	get_cosine(t_vec vec1, t_vec vec2)
{
	return (vec_dot(vec1, vec2) / (vec_scalar(vec1) * vec_scalar(vec2)));
}
