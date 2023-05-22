/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_lighting_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/09 16:09:50 by jpark2            #+#    #+#             */
/*   Updated: 2023/03/08 15:58:26 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static t_vec	diff_spec(t_mlx_arg *mlx_arg, t_light *light, \
				t_hit_record *rec, t_ref flag)
{
	t_vec	surf_to_light;
	t_vec	reflected;
	t_vec	color;

	surf_to_light = vec_diff(light->point, rec->p);
	if (shadow_check(mlx_arg, rec->p, surf_to_light))
		return (vec(0, 0, 0));
	color = calc_gradation(rec->surface.color, \
		color_resize(get_cosine(rec->normal, surf_to_light)), \
		light->color, \
		light_attenuation(light->brightness, vec_scalar(surf_to_light)));
	if (flag == REFLECT_FULL_PHONG)
	{
		reflected = vec_reflect(mlx_arg->ray.dir, rec->normal);
		color = vec_plus(color, calc_gradation(light->color, \
			color_resize(\
			(get_cosine(reflected, surf_to_light) - 0.98) * 50), light->color, \
			light_attenuation(light->brightness, vec_scalar(surf_to_light))));
	}
	return (color);
}

static t_vec	phong_color(t_vec color, t_vec phong, t_mlx_arg *mlx_arg)
{
	double	r;
	double	g;
	double	b;
	t_vec	ambient;

	(void)phong;
	ambient = mlx_arg->ambient;
	r = color.x * ambient.x;
	g = color.y * ambient.y;
	b = color.z * ambient.z;
	r = r * 0.2 + phong.x * 0.8;
	g = g * 0.2 + phong.y * 0.8;
	b = b * 0.2 + phong.z * 0.8;
	r = color_resize(r);
	g = color_resize(g);
	b = color_resize(b);
	return (vec(r, g, b));
}

t_vec	phong_lighting(t_mlx_arg *mlx_arg, t_hit_record *rec)
{
	t_light	*temp;
	t_vec	curr_color;
	t_vec	color;

	if (vec_cmp(rec->surface.color, vec(-2, -2, -2)) == 0)
		rec->surface.color = get_texture(rec, rec->u, rec->v);
	else if (vec_cmp(rec->surface.color, vec(-1, -1, -1)) == 0)
		rec->surface.color = check_texture(rec->u, rec->v);
	color = vec(0, 0, 0);
	temp = mlx_arg->lights;
	while (temp != NULL)
	{
		curr_color = diff_spec(mlx_arg, temp, rec, mlx_arg->ref_type);
		color = vec_plus(color, curr_color);
		temp = temp->next;
	}
	return (phong_color(rec->surface.color, color, mlx_arg));
}
