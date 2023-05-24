/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:42:29 by jpark2            #+#    #+#             */
/*   Updated: 2023/03/08 15:58:26 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	get_plane_uv(t_plane plane, t_vec p, double *u, double *v)
{
	t_vec	cent_to_surf;
	t_vec	axis_x;
	t_vec	axis_y;
	double	x;
	double	y;

	cent_to_surf = vec_diff(p, plane.point);
	axis_x = vec_cross((t_vec){0, 1, 0}, plane.normal);
	if (vec_cmp(axis_x, vec(0, 0, 0)) == 0)
		axis_x = vec(1, 0, 0);
	axis_y = vec_cross(axis_x, plane.normal);
	x = vec_dot(axis_x, cent_to_surf) / 1000;
	y = vec_dot(axis_y, cent_to_surf) / 1000;
	*u = ft_abs(x - (int)x);
	*v = ft_abs(y - (int)y);
}

double	plane_hit(t_plane plane, t_ray ray)
{
	double	dn;
	double	t;

	dn = vec_dot(plane.normal, ray.dir);
	if (dn == 0)
		return (-1);
	t = (vec_dot(plane.normal, vec_diff(plane.point, ray.org))) / dn;
	if (t < DBL_EPSL)
		return (-1);
	return (t);
}

int	rec_plane_hit(t_plane plane, t_ray ray, double t_max, t_hit_record *rec)
{
	double	root;

	root = plane_hit(plane, ray);
	if (root == -1 || root > t_max)
		return (0);
	rec->t = root;
	rec->p = ray_at(&ray, rec->t);
	rec->normal = plane.normal;
	set_face_normal(ray, rec);
	rec->surface = plane.surface;
	get_plane_uv(plane, rec->p, &rec->u, &rec->v);
	rec->obj_type = OBJ_PLANE;
	return (1);
}

t_vec	plane_normal_vec(t_ray ray, t_plane plane, double t)
{
	t_vec	surf;

	surf = vec_plus(vec_mul(ray.dir, t), ray.org);
	if (vec_dot(surf, plane.normal) < 0)
		return (vec_mul(plane.normal, -1));
	else
		return (plane.normal);
}
