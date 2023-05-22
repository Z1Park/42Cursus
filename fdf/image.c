/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 09:40:35 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/05 20:33:08 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	img_black_screen(t_hook_var *vars)
{
	int				i;
	int				j;
	unsigned int	*data;

	data = (unsigned int *)(vars->black_screen->addr);
	i = 0;
	while (i <= vars->map->height)
	{
		j = 0;
		while (j <= vars->map->width)
		{
			data[i * MAX_WIDTH + j] = 0x00000000;
			j++;
		}
		i++;
	}
}

static void	img_para_front(t_hook_var *var, int gap, t_cod_2d from, t_cod_2d to)
{
	int			i;
	int			j;

	i = -1;
	while (++i < var->map->height)
	{
		j = -1;
		while (++j < var->map->width)
		{
			from = set_2d_value1(var->map->width * gap, j * gap, \
				var->map->data[i][j] * gap, var->map->color[i][j]);
			if (i != var->map->height - 1)
			{
				to = set_2d_value1(var->map->width * gap, j * gap, \
					var->map->data[i + 1][j] * gap, var->map->color[i][j]);
				img_draw_2d_line(var->para_front->addr, from, to);
			}
			if (j != var->map->width - 1)
			{
				to = set_2d_value1(var->map->width * gap, (j + 1) * gap, \
					var->map->data[i][j + 1] * gap, var->map->color[i][j]);
				img_draw_2d_line(var->para_front->addr, from, to);
			}
		}
	}
}

static void	img_para_side(t_hook_var *var, int gap, t_cod_2d from, t_cod_2d to)
{
	int			i;
	int			j;

	i = -1;
	while (++i < var->map->height)
	{
		j = -1;
		while (++j < var->map->width)
		{
			from = set_2d_value1(var->map->height * gap, i * gap, \
				var->map->data[i][j] * gap, var->map->color[i][j]);
			if (i != var->map->height - 1)
			{
				to = set_2d_value1(var->map->height * gap, (i + 1) * gap, \
					var->map->data[i + 1][j] * gap, var->map->color[i][j]);
				img_draw_2d_line(var->para_side->addr, from, to);
			}
			if (j != var->map->width - 1)
			{
				to = set_2d_value1(var->map->height * gap, i * gap, \
					var->map->data[i][j + 1] * gap, var->map->color[i][j]);
				img_draw_2d_line(var->para_side->addr, from, to);
			}
		}
	}
}

static void	img_para_top(t_hook_var *var, int gap, t_cod_2d from, t_cod_2d to)
{
	int			i;
	int			j;

	i = -1;
	while (++i < var->map->height)
	{
		j = -1;
		while (++j < var->map->width)
		{
			from.x = (MAX_WIDTH - var->map->width * gap) / 2 + j * gap;
			from.y = (MAX_HEIGHT - var->map->height * gap) / 2 + i * gap;
			from.color = var->map->color[i][j];
			if (i != var->map->height - 1)
			{
				to = set_2d_value2(var->map, i + 1, j, gap);
				img_draw_2d_line(var->para_top->addr, from, to);
			}
			if (j != var->map->width - 1)
			{
				to = set_2d_value2(var->map, i, j + 1, gap);
				img_draw_2d_line(var->para_top->addr, from, to);
			}
		}
	}
}

void	set_images(t_hook_var *vars)
{
	int			gap;
	t_cod_2d	from;
	t_cod_2d	to;

	from.x = 0;
	from.y = 0;
	to.x = 0;
	to.y = 0;
	vars->black_screen = make_image(vars->var);
	vars->para_front = make_image(vars->var);
	vars->para_side = make_image(vars->var);
	vars->para_top = make_image(vars->var);
	img_black_screen(vars);
	gap = gap_resize(vars, vars->map->width, get_max_height(vars));
	img_para_front(vars, gap, from, to);
	gap = gap_resize(vars, vars->map->height, get_max_height(vars));
	img_para_side(vars, gap, from, to);
	gap = gap_resize(vars, vars->map->width, vars->map->height);
	img_para_top(vars, gap, from, to);
}
