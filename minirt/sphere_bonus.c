/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 15:08:53 by jpark2            #+#    #+#             */
/*   Updated: 2023/03/08 15:58:19 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	get_sphere_uv(t_vec normal, double *u, double *v)
{
	double	theta;
	double	phi;

	theta = acos(-normal.z);
	phi = atan2(-normal.y, normal.x) + M_PI;
	*u = phi / (2 * M_PI);
	*v = theta / M_PI;
}

double	sphere_hit(t_sphere sphere, t_ray ray)
{
	const t_vec		sp_vec = vec_diff(sphere.center, ray.org);
	const double	a = vec_dot(ray.dir, ray.dir);
	const double	b = -1 * vec_dot(sp_vec, ray.dir);
	const double	c = vec_dot(sp_vec, sp_vec) - sphere.radius * sphere.radius;
	double			root;

	if (b * b - a * c < 0)
		return (-1);
	root = (-b - sqrt(b * b - a * c)) / a;
	if (root < DBL_EPSL)
	{
		root = (-b + sqrt(b * b - a * c)) / a;
		if (root < DBL_EPSL)
			return (-1);
	}
	return (root);
}

int	rec_sp_hit(t_sphere sp, t_ray ray, double t_max, t_hit_record *rec)
{
	double	root;

	root = sphere_hit(sp, ray);
	if (root == -1 || root > t_max)
		return (0);
	rec->t = root;
	rec->p = ray_at(&ray, rec->t);
	rec->normal = vec_div(vec_diff(rec->p, sp.center), sp.radius);
	set_face_normal(ray, rec);
	rec->surface = sp.surface;
	get_sphere_uv(rec->normal, &rec->u, &rec->v);
	rec->obj_type = OBJ_SPHERE;
	return (1);
}
