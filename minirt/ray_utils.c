/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingkang <mingkang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 16:09:47 by mingkang          #+#    #+#             */
/*   Updated: 2023/03/07 21:21:35 by mingkang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_face_normal(t_ray ray, t_hit_record *rec)
{
	if (vec_dot(ray.dir, rec->normal) > 0.0)
	{
		rec->normal = vec_mul(rec->normal, -1);
		rec->front_face = -1;
	}
	else
		rec->front_face = 0;
}

t_vec	ray_at(t_ray *ray, double t)
{
	t_vec	out;

	out.x = ray->org.x + ray->dir.x * t;
	out.y = ray->org.y + ray->dir.y * t;
	out.z = ray->org.z + ray->dir.z * t;
	return (out);
}
