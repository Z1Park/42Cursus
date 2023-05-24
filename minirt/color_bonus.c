/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 14:21:28 by jpark2            #+#    #+#             */
/*   Updated: 2023/03/08 15:59:06 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_vec	calc_gradation(t_vec color, double ratio, t_vec light, double t)
{
	double	red;
	double	green;
	double	blue;

	if (ratio > 1)
		ratio = 1;
	red = color.x * ratio;
	green = color.y * ratio;
	blue = color.z * ratio;
	if (t > 1)
		t = 1;
	red = red * light.x * t;
	green = green * light.y * t;
	blue = blue * light.z * t;
	return (vec(red, green, blue));
}

t_vec	set_background_color(t_mlx_arg *mlx_arg, double u, double v)
{
	int					x;
	int					y;
	unsigned int		color;

	if (mlx_arg->background.texture.img == NULL || u < 0 || v < 0)
	{
		return (mlx_arg->background.color);
	}
	else
	{
		x = (int)((1 - u) * mlx_arg->cam.img_width);
		y = (int)((1 - v) * mlx_arg->cam.img_height);
		color = *(unsigned int *)(mlx_arg->background.texture.addr + \
			(y * mlx_arg->background.texture.size_line + \
			x * (mlx_arg->background.texture.bpp / 8)));
		return (vec((double)get_r(color) / 255, \
					(double)get_g(color) / 255, \
					(double)get_b(color) / 255));
	}
}

t_vec	ray_color(t_ray r, t_mlx_arg *mlx_arg, int depth)
{
	t_hit_record	rec;
	t_vec			color;
	t_ray			scattered;

	if (depth <= 0)
		return (vec(0, 0, 0));
	if (shortest_hit(mlx_arg, r, &rec))
	{
		if (vec_cmp(rec.surface.color, vec(-2, -2, -2)) == 0)
			rec.surface.color = get_texture(&rec, rec.u, rec.v);
		else if (vec_cmp(rec.surface.color, vec(-1, -1, -1)) == 0)
			rec.surface.color = check_texture(rec.u, rec.v);
		if (rec.surface.mat == WOOD && \
				scatter_lamb(r, &rec, &color, &scattered))
			return (vec_mul2(ray_color(scattered, mlx_arg, depth - 1), color));
		else if ((rec.surface.mat == METAL || rec.surface.mat == MIRROR) && \
				scatter_metal(r, &rec, &color, &scattered))
			return (vec_mul2(ray_color(scattered, mlx_arg, depth - 1), color));
		else if (rec.surface.mat == GLASS && \
				scatter_glass(r, &rec, &color, &scattered))
			return (vec_mul2(ray_color(scattered, mlx_arg, depth - 1), color));
		return (vec(0, 0, 0));
	}
	return (set_background_color(mlx_arg, -1, -1));
}

int	write_color(t_vec *color, int num)
{
	double	scale;

	if (num == 0)
		num = 1;
	scale = 1 / (double)num;
	color->x = clamp(sqrt(color->x * scale), 0.0, 0.999);
	color->y = clamp(sqrt(color->y * scale), 0.0, 0.999);
	color->z = clamp(sqrt(color->z * scale), 0.0, 0.999);
	return ((int)(255 * color->x) << 16 | (int)(255 * color->y) << 8 \
			| (int)(255 * color->z));
}

double	color_resize(double color)
{
	if (color > 1)
		return (1);
	if (color < 0)
		return (0);
	return (color);
}
