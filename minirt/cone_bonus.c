/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/02 15:51:38 by mingkang          #+#    #+#             */
/*   Updated: 2023/03/08 15:59:04 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	get_cone_uv(t_cone cone, t_hit_record *rec, double *u, double *v)
{
	double	phi;
	t_vec	axis_x;
	t_vec	axis_y;
	double	x;
	double	y;

	axis_x = vec_unit(vec_cross(vec(0, 1, 0), cone.normal));
	if (vec_cmp(axis_x, vec(0, 0, 0)) == 0)
		axis_x = vec(1, 0, 0);
	axis_y = vec_cross(axis_x, cone.normal);
	x = vec_dot(axis_x, rec->normal);
	y = vec_dot(axis_y, rec->normal);
	phi = atan2(-y, -x) + M_PI;
	*u = phi / (2 * M_PI);
	*v = ft_abs(vec_dot(cone.normal, vec_diff(rec->p, cone.center)) \
				/ cone.height);
}

static int	height_check(t_cone cone, t_vec cent_to_surf)
{
	double	temp;

	temp = vec_dot(cone.normal, cent_to_surf);
	if (cone.height > 0)
	{
		if (temp < 0 || temp > cone.height)
			return (-1);
	}
	else
	{
		if (temp < cone.height || temp > -cone.height)
			return (-1);
	}
	return (0);
}

double	cone_hit(t_cone cone, t_ray ray)
{
	const t_vec		vec_ce = vec_diff(ray.org, cone.center);
	const double	a = pow(vec_dot(ray.dir, cone.normal), 2.0) \
						- pow(cone.cosine, 2.0);
	const double	b = vec_dot(ray.dir, cone.normal) \
						* vec_dot(vec_ce, cone.normal) \
						- vec_dot(vec_ce, ray.dir) * pow(cone.cosine, 2.0);
	const double	c = pow(vec_dot(vec_ce, cone.normal), 2.0) \
						- vec_dot(vec_ce, vec_ce) * pow(cone.cosine, 2.0);
	double			root;

	if (b * b - a * c < 0)
		return (-1);
	root = ((-b + sqrt(b * b - a * c))) / a;
	if (root < DBL_EPSL || \
		height_check(cone, vec_plus(vec_ce, vec_mul(ray.dir, root))) < 0)
	{
		root = ((-b - sqrt(b * b - a * c))) / a;
		if (root < DBL_EPSL || \
			height_check(cone, vec_plus(vec_ce, vec_mul(ray.dir, root))) < 0)
			return (-1);
	}
	return (root);
}

t_vec	cone_normal_vec(t_vec p, t_cone cone)
{
	t_vec	cp;
	t_vec	normal;

	cp = vec_diff(p, cone.center);
	normal = vec_mul(cone.normal, vec_dot(cp, cp) / vec_dot(cp, cone.normal));
	normal = vec_diff(cp, normal);
	return (vec_unit(normal));
}

int	rec_cone_hit(t_cone cone, t_ray ray, double t_max, t_hit_record *rec)
{
	double	root;

	root = cone_hit(cone, ray);
	if (root == -1 || root > t_max)
		return (0);
	rec->t = root;
	rec->p = ray_at(&ray, rec->t);
	rec->normal = cone_normal_vec(rec->p, cone);
	set_face_normal(ray, rec);
	rec->surface = cone.surface;
	get_cone_uv(cone, rec, &rec->u, &rec->v);
	rec->obj_type = OBJ_CONE;
	return (1);
}
