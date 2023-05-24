/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scatter.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 22:13:39 by mingkang          #+#    #+#             */
/*   Updated: 2023/03/09 16:12:03 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

double	reflectance(double cos_theta, double ref_ratio)
{
	double	r0;
	double	rfl;

	r0 = (1 - ref_ratio) / (1 + ref_ratio);
	r0 = r0 * r0;
	rfl = r0 + (1 - r0) * pow((1 - cos_theta), 5);
	return (rfl);
}

int	near_zero(t_vec v)
{
	const double	limit = 0.001;

	return ((v.x < limit) && (v.y < limit) && (v.z < limit));
}

int	scatter_lamb(t_ray r, t_hit_record *rec, t_vec *color, t_ray *sct)
{
	t_vec	scatter_dir;

	(void)r;
	scatter_dir = vec_plus(rec->normal, random_unit_vec());
	if (near_zero(scatter_dir) != 0)
		scatter_dir = rec->normal;
	sct->org = rec->p;
	sct->dir = vec_unit(scatter_dir);
	*color = rec->surface.color;
	return (1);
}

int	scatter_metal(t_ray r, t_hit_record *rec, t_vec *color, t_ray *sct)
{
	t_vec	reflected_dir;

	reflected_dir = vec_reflect(vec_unit(r.dir), rec->normal);
	sct->org = rec->p;
	if (rec->surface.mat == METAL)
		sct->dir = vec_unit(vec_plus(reflected_dir, \
					vec_mul(rand_in_unit_sphere(), 0.5)));
	else
		sct->dir = vec_unit(reflected_dir);
	*color = rec->surface.color;
	return (vec_dot(sct->dir, rec->normal) > 0);
}

int	scatter_glass(t_ray r, t_hit_record *rec, t_vec *color, t_ray *sct)
{
	double	cos_theta;
	double	sin_theta;
	double	ref_ratio;
	t_vec	unit_vec;
	t_vec	direction;

	if (rec->front_face)
		ref_ratio = 1.5;
	else
		ref_ratio = 1.0 / 1.5;
	*color = vec(1.0, 1.0, 1.0);
	unit_vec = vec_unit(r.dir);
	cos_theta = fmin(vec_dot(vec_neg(unit_vec), rec->normal), 1.0);
	sin_theta = sqrt(1.0 - cos_theta * cos_theta);
	if (ref_ratio * sin_theta > 1.0 || \
		reflectance(cos_theta, ref_ratio) > rand_double())
		direction = vec_reflect(unit_vec, rec->normal);
	else
		direction = vec_refract(unit_vec, rec->normal, ref_ratio);
	sct->org = rec->p;
	sct->dir = direction;
	return (1);
}
