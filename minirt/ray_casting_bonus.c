/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 20:34:38 by jpark2            #+#    #+#             */
/*   Updated: 2023/03/08 15:58:24 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	set_ray(t_camera *cam, t_ray *r, double i, double j)
{
	double	s;
	double	t;
	t_vec	rd;
	t_vec	offset;

	rd = vec_mul(rand_in_unit_disk(), cam->lens_radius);
	offset = vec_plus(vec_mul(cam->u, rd.x), vec_mul(cam->v, rd.y));
	s = (i + rand_double()) / (cam->img_width - 1);
	t = (j + rand_double()) / (cam->img_height - 1);
	r->org = vec_plus(cam->origin, offset);
	r->dir = \
		vec(cam->left_bot.x + s * cam->horizon.x + t * cam->vert.x - r->org.x, \
			cam->left_bot.y + s * cam->horizon.y + t * cam->vert.y - r->org.y, \
			cam->left_bot.z + s * cam->horizon.z + t * cam->vert.z - r->org.z);
	r->dir = vec_unit(r->dir);
}

static t_vec	check_ray_hit(t_mlx_arg *mlx_arg, int i, int j)
{
	t_hit_record	rec;
	int				max_depth;

	max_depth = 50;
	if (mlx_arg->ref_type == REFLECT_PHONG \
		|| mlx_arg->ref_type == REFLECT_FULL_PHONG)
	{
		if (shortest_hit(mlx_arg, mlx_arg->ray, &rec))
			return (phong_lighting(mlx_arg, &rec));
		else
			return (set_background_color(mlx_arg, \
				((double)i / mlx_arg->cam.img_width), \
				((double)j / mlx_arg->cam.img_height)));
	}
	else if (mlx_arg->ref_type == REFLECT_RAY_TRACING)
		return (ray_color(mlx_arg->ray, mlx_arg, max_depth));
	return (vec(0, 0, 0));
}

void	ray_casting(t_mlx_arg *mlx_arg)
{
	int		i;
	int		j;
	int		s;
	t_vec	color;

	j = mlx_arg->cam.img_height;
	while (j >= 0)
	{
		i = 0;
		while (i <= mlx_arg->cam.img_width)
		{
			color = (t_vec){0, 0, 0};
			s = -1;
			while (s++ < ALIAS)
			{
				set_ray(&mlx_arg->cam, &mlx_arg->ray, i, j);
				color = vec_plus(color, check_ray_hit(mlx_arg, i, j));
			}
			put_pixel(mlx_arg, i, mlx_arg->cam.img_height - j, \
						write_color(&color, ALIAS));
			i++;
		}
		j--;
	}
	mlx_put_image_to_window(mlx_arg->mlx, mlx_arg->win, mlx_arg->img, 0, 0);
}
