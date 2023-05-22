/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:34:22 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/05 20:31:38 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	img_draw_2d_line(char *addr, t_cod_2d from, t_cod_2d to)
{
	unsigned int	*data;
	int				i;
	int				gap;

	data = (unsigned int *)addr;
	gap = get_max(absolute(to.x - from.x), absolute(to.y - from.y));
	i = 0;
	while (i <= gap && gap != 0)
	{
		data[(from.y + (to.y - from.y) * i / gap) * MAX_WIDTH \
			+ from.x + (to.x - from.x) * i / gap] = \
			from.color + (to.color - from.color) * i / gap;
		i++;
	}
}

int	get_max_height(t_hook_var *vars)
{
	int	i;
	int	j;
	int	height_max;

	height_max = 0;
	i = 0;
	while (i < vars->map->height)
	{
		j = 0;
		while (j < vars->map->width)
		{
			if (height_max < vars->map->data[i][j])
				height_max = vars->map->data[i][j];
			j++;
		}
		i++;
	}
	return (height_max);
}

int	gap_resize(t_hook_var *vars, int w, int h)
{
	int	gap;

	gap = vars->map->gap_pixel;
	while (w * gap > MAX_WIDTH - 200 && gap > 2 && h * gap > MAX_HEIGHT - 200)
		gap--;
	while (w * gap < MAX_WIDTH - 200 && h * gap < MAX_HEIGHT - 200)
		gap++;
	return (gap);
}

t_cod_2d	set_2d_value1(int x1, int x2, int y, int color)
{
	t_cod_2d	tmp;

	tmp.x = (MAX_WIDTH - x1) / 2 + x2;
	tmp.y = MAX_HEIGHT - 60 - y;
	tmp.color = color;
	return (tmp);
}

t_cod_2d	set_2d_value2(t_map *map, int i, int j, int gap)
{
	t_cod_2d	tmp;

	tmp.x = (MAX_WIDTH - map->width * gap) / 2 + j * gap;
	tmp.y = (MAX_HEIGHT - map->height * gap) / 2 + i * gap;
	tmp.color = map->color[i][j];
	return (tmp);
}
