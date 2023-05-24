/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/13 09:13:22 by jpark2            #+#    #+#             */
/*   Updated: 2023/03/08 12:56:01 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	shadow_check(t_mlx_arg *mlx_arg, t_vec surf, t_vec dir)
{
	t_obj_list	*node;
	double		hit;
	t_ray		tmp_ray;

	node = mlx_arg->obj_list;
	hit = -1;
	tmp_ray.dir = vec_unit(dir);
	tmp_ray.org = surf;
	while (node != NULL)
	{
		if (node->obj_type == OBJ_SPHERE)
			hit = sphere_hit(*(t_sphere *)node->obj, tmp_ray);
		else if (node->obj_type == OBJ_PLANE)
			hit = plane_hit(*(t_plane *)node->obj, tmp_ray);
		else if (node->obj_type == OBJ_CYLINDER)
			hit = cylinder_hit(*(t_cylinder *)node->obj, tmp_ray);
		else if (node->obj_type == OBJ_CONE)
			hit = cone_hit(*(t_cone *)node->obj, tmp_ray);
		if (hit > DBL_EPSL && vec_scalar(dir) >= hit)
			return (1);
		node = node->next;
	}
	return (0);
}
