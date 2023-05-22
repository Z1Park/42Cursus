/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_hit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingkang <mingkang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 15:09:03 by jpark2            #+#    #+#             */
/*   Updated: 2023/03/07 21:21:06 by mingkang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_hit(t_obj_list *object, t_ray ray, double t_max, t_hit_record *rec)
{
	int	is_hit;

	is_hit = 0;
	if (object->obj_type == OBJ_SPHERE)
		is_hit = rec_sp_hit(*(t_sphere *)object->obj, ray, t_max, rec);
	else if (object->obj_type == OBJ_PLANE)
		is_hit = rec_plane_hit(*(t_plane *)object->obj, ray, t_max, rec);
	else if (object->obj_type == OBJ_CYLINDER)
		is_hit = rec_cy_hit(*(t_cylinder *)object->obj, ray, t_max, rec);
	else if (object->obj_type == OBJ_CONE)
		is_hit = rec_cone_hit(*(t_cone *)object->obj, ray, t_max, rec);
	return (is_hit);
}

int	shortest_hit(t_mlx_arg *mlx_arg, t_ray ray, t_hit_record *rec)
{
	int				hit;
	double			closest_so_far;
	t_hit_record	tmp_rec;
	t_obj_list		*temp;

	hit = 0;
	closest_so_far = __DBL_MAX__;
	temp = mlx_arg->obj_list;
	while (temp != NULL)
	{
		if (get_hit(temp, ray, closest_so_far, &tmp_rec))
		{
			hit = 1;
			closest_so_far = tmp_rec.t;
			*rec = tmp_rec;
		}
		temp = temp->next;
	}
	return (hit);
}
