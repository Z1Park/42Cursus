/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingkang <mingkang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 12:42:55 by jpark2            #+#    #+#             */
/*   Updated: 2023/03/07 21:25:15 by mingkang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	get_cylinder_uv(t_cylinder cy, t_hit_record *rec, double *u, double *v)
{
	double	phi;
	t_vec	axis_x;
	t_vec	axis_y;
	double	x;
	double	y;

	axis_x = vec_unit(vec_cross(vec(0, 1, 0), cy.normal));
	if (vec_cmp(axis_x, vec(0, 0, 0)) == 0)
		axis_x = vec(1, 0, 0);
	axis_y = vec_cross(axis_x, cy.normal);
	x = vec_dot(axis_x, rec->normal);
	y = vec_dot(axis_y, rec->normal);
	phi = atan2(-y, -x) + M_PI;
	*u = phi / (2 * M_PI);
	*v = vec_dot(cy.normal, vec_diff(rec->p, cy.center)) / cy.height;
}

static int	height_check(t_cylinder cylinder, t_vec cent_to_surf)
{
	double	temp;

	temp = vec_dot(cent_to_surf, cylinder.normal);
	if (temp < 0 || temp > cylinder.height)
		return (-1);
	return (0);
}

double	cylinder_hit(t_cylinder cy, t_ray ray)
{
	const t_vec		vec_co = vec_diff(ray.org, cy.center);
	const double	a = pow(vec_dot(ray.dir, cy.normal), 2.0) - 1;
	const double	b = vec_dot(ray.dir, cy.normal) * \
					vec_dot(vec_co, cy.normal) - vec_dot(vec_co, ray.dir);
	const double	c = pow(cy.diameter, 2.0) - vec_dot(vec_co, vec_co) \
					+ pow(vec_dot(vec_co, cy.normal), 2.0);
	double			root;

	if (b * b - a * c < 0)
		return (-1);
	root = ((-b + sqrt(b * b - a * c))) / a;
	if (root < DBL_EPSL || \
		height_check(cy, vec_plus(vec_co, vec_mul(ray.dir, root))) < 0)
	{
		root = ((-b - sqrt(b * b - a * c))) / a;
		if (root < DBL_EPSL || \
			height_check(cy, vec_plus(vec_co, vec_mul(ray.dir, root))) < 0)
			return (-1);
	}
	return (root);
}

t_vec	cylinder_normal_vec(t_vec p, t_cylinder cy)
{
	t_vec	cp;
	t_vec	normal;

	cp = vec_diff(p, cy.center);
	normal = vec_diff(cp, vec_mul(cy.normal, vec_dot(cp, cy.normal)));
	return (vec_unit(normal));
}

int	rec_cy_hit(t_cylinder cy, t_ray ray, double t_max, t_hit_record *rec)
{
	double	root;

	root = cylinder_hit(cy, ray);
	if (root == -1 || root > t_max)
		return (0);
	rec->t = root;
	rec->p = ray_at(&ray, rec->t);
	rec->normal = cylinder_normal_vec(rec->p, cy);
	set_face_normal(ray, rec);
	rec->surface = cy.surface;
	get_cylinder_uv(cy, rec, &rec->u, &rec->v);
	rec->obj_type = OBJ_CYLINDER;
	return (1);
}
