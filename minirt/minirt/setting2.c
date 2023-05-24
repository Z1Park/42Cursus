/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/08 13:01:41 by jpark2            #+#    #+#             */
/*   Updated: 2023/03/08 13:02:23 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_light	*add_light_list(t_mlx_arg *mlx_arg)
{
	t_light	*temp;

	if (mlx_arg->lights == NULL)
	{
		mlx_arg->lights = malloc(sizeof(t_light));
		if (mlx_arg->lights == NULL)
			error_exit("Error\nmalloc fail\n");
		temp = mlx_arg->lights;
	}
	else
	{
		temp = mlx_arg->lights;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = malloc(sizeof(t_light));
		if (temp->next == NULL)
			error_exit("Error\nmalloc fail\n");
		temp = temp->next;
	}
	temp->next = NULL;
	return (temp);
}

void	add_light(t_mlx_arg *mlx_arg, char **argv)
{
	char		**point;
	char		**color;
	t_light		*node;

	if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL)
		error_exit("Error\nlight argument error\n");
	point = ft_split(argv[1], ',');
	if (get_argv_size(point) != 3)
		error_exit("Error\nlight argument error\n");
	color = ft_split(argv[3], ',');
	if (get_argv_size(color) != 3)
		error_exit("Error\nlight argument error\n");
	node = add_light_list(mlx_arg);
	node->brightness = ft_atod(argv[2]);
	if (node->brightness < 0 || node->brightness > 1)
		error_exit("Error\nlight argument error\n");
	node->point = (t_vec){ft_atod(point[0]), \
				ft_atod(point[1]), ft_atod(point[2])};
	node->color = vec((double)ft_error_atoi(color[0]) / 255, \
								(double)ft_error_atoi(color[1]) / 255, \
								(double)ft_error_atoi(color[2]) / 255);
	argv_free(point);
	argv_free(color);
}

t_material	get_material_type(char *str)
{
	if (str == NULL)
		return (WOOD);
	if (ft_strcmp(str, "G\n") == 0)
		return (GLASS);
	if (ft_strcmp(str, "MR\n") == 0)
		return (MIRROR);
	if (ft_strcmp(str, "MT\n") == 0)
		return (METAL);
	if (ft_strcmp(str, "W\n") == 0)
		return (WOOD);
	error_exit("Error\nmaterial type is wrong(G, MR, MT, W)\n");
	return (0);
}
