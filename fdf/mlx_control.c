/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 09:36:23 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/05 19:37:00 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_vars	*init_and_set_window(t_map *map)
{
	t_vars	*mlx_var;

	mlx_var = malloc(sizeof(t_vars));
	if (mlx_var == NULL)
		print_error(ERR_ALLOC_FAIL, NULL);
	mlx_var->mlx = mlx_init();
	while (map->gap_pixel > 2
		&& (map->width * map->gap_pixel > MAX_WIDTH - AREA_MARGIN * 8
			|| map->height * map->gap_pixel > MAX_HEIGHT - AREA_MARGIN * 8))
		map->gap_pixel--;
	mlx_var->win = mlx_new_window(mlx_var->mlx, MAX_WIDTH, MAX_HEIGHT, "fdf");
	return (mlx_var);
}

t_img	*make_image(t_vars *var)
{
	t_img	*img;

	img = malloc(sizeof(t_img));
	if (img == NULL)
		print_error(ERR_ALLOC_FAIL, NULL);
	img->img = mlx_new_image(var->mlx, MAX_WIDTH, MAX_HEIGHT);
	if (img->img == NULL)
		print_error(ERR_ALLOC_FAIL, NULL);
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel), \
		&(img->size_line), &(img->endian));
	return (img);
}

static void	draw_3d_line(t_map *map, t_vars *var, t_line_3d cods, t_cod_2d *ori)
{
	t_cod_2d	tmp1;
	t_cod_2d	tmp2;
	int			pixels;
	int			i;

	tmp1 = calculate_2d_pos(cods.from, map->gap_pixel);
	tmp2 = calculate_2d_pos(cods.to, map->gap_pixel);
	pixels = get_max(absolute(tmp2.x - tmp1.x), absolute(tmp2.y - tmp1.y));
	i = 0;
	while (i <= pixels && pixels != 0)
	{
		mlx_pixel_put(var->mlx, var->win, \
			ori->x + tmp1.x + (tmp2.x - tmp1.x) * i / pixels, \
			ori->y + tmp1.y + (tmp2.y - tmp1.y) * i / pixels, \
			tmp1.color + (tmp2.color - tmp1.color) * i / pixels);
		i++;
	}
}

void	draw_map(t_map *map, t_vars *var, t_cod_3d **cod, t_cod_2d *ori)
{
	int			i;
	int			j;
	t_line_3d	cods;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			cods.from = cod[i][j];
			if (i != map->height - 1)
			{
				cods.to = cod[i + 1][j];
				draw_3d_line(map, var, cods, ori);
			}
			if (j != map->width - 1)
			{
				cods.to = cod[i][j + 1];
				draw_3d_line(map, var, cods, ori);
			}
			j++;
		}
		i++;
	}
}
