/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coordinate.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 09:15:51 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/05 19:35:10 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_cod_3d	**make_coordinate(t_map *map)
{
	t_cod_3d	**ptr;
	int			i;

	ptr = malloc(sizeof(t_cod_3d *) * map->height);
	if (ptr == NULL)
		print_error(ERR_ALLOC_FAIL, NULL);
	i = 0;
	while (i < map->height)
	{
		ptr[i] = malloc(sizeof(t_cod_3d) * map->width);
		if (ptr[i] == NULL)
			print_error(ERR_ALLOC_FAIL, NULL);
		i++;
	}
	return (ptr);
}

void	map_to_coordinate(t_map *map, t_cod_3d **cod)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			cod[i][j].x = i;
			cod[i][j].y = j;
			cod[i][j].z = map->data[i][j];
			cod[i][j].color = map->color[i][j];
			j++;
		}
		i++;
	}
}

t_cod_2d	calculate_2d_pos(t_cod_3d cod, int gap)
{
	t_cod_2d	pos;
	double		theta;

	theta = 26.565 * M_PI / 180;
	pos.x = round((cod.x - cod.y) * cos(theta) * gap);
	pos.y = round(((-cod.x - cod.y) * sin(theta) - cod.z) * gap);
	pos.color = cod.color;
	return (pos);
}
