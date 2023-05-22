/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 16:32:00 by jpark2            #+#    #+#             */
/*   Updated: 2023/03/08 15:58:27 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

t_obj_list	*add_object(t_mlx_arg *mlx_arg, t_obj obj_type)
{
	t_obj_list	*temp;

	if (mlx_arg->obj_list == NULL)
	{
		mlx_arg->obj_list = malloc(sizeof(t_obj_list));
		if (mlx_arg->obj_list == NULL)
			error_exit("Error\nmalloc fail\n");
		temp = mlx_arg->obj_list;
	}
	else
	{
		temp = mlx_arg->obj_list;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = malloc(sizeof(t_obj_list));
		if (temp->next == NULL)
			error_exit("Error\nmalloc fail\n");
		temp = temp->next;
	}
	temp->obj_type = obj_type;
	temp->next = NULL;
	return (temp);
}

void	add_sphere(t_mlx_arg *mlx_arg, char **argv)
{
	t_obj_list	*node;

	if (get_argv_size(argv) <= 3)
		error_exit("Error\nObject argument error\n");
	node = add_object(mlx_arg, OBJ_SPHERE);
	node->obj = ft_calloc(1, sizeof(t_sphere));
	if (node->obj == NULL)
		error_exit("Error\nmalloc fail\n");
	((t_sphere *)node->obj)->radius = ft_atod(argv[2]);
	((t_sphere *)node->obj)->center = string_to_vec(argv[1]);
	check_color_pattern(mlx_arg, &((t_sphere *)node->obj)->surface, argv[3]);
	((t_sphere *)node->obj)->surface.mat = get_material_type(argv[4]);
}

void	add_plane(t_mlx_arg *mlx_arg, char **argv)
{
	t_obj_list	*node;

	if (get_argv_size(argv) <= 3)
		error_exit("Error\nObject argument error\n");
	node = add_object(mlx_arg, OBJ_PLANE);
	node->obj = ft_calloc(1, sizeof(t_plane));
	if (node->obj == NULL)
		error_exit("Error\nmalloc fail\n");
	((t_plane *)node->obj)->point = string_to_vec(argv[1]);
	((t_plane *)node->obj)->normal = vec_unit(string_to_vec(argv[2]));
	check_color_pattern(mlx_arg, &((t_plane *)node->obj)->surface, argv[3]);
	((t_plane *)node->obj)->surface.mat = get_material_type(argv[4]);
}

void	add_cylinder(t_mlx_arg *mlx_arg, char **argv)
{
	t_obj_list	*node;

	if (get_argv_size(argv) <= 5)
		error_exit("Error\nObject argument error\n");
	node = add_object(mlx_arg, OBJ_CYLINDER);
	node->obj = ft_calloc(1, sizeof(t_cylinder));
	if (node->obj == NULL)
		error_exit("Error\nmalloc fail\n");
	((t_cylinder *)node->obj)->center = string_to_vec(argv[1]);
	((t_cylinder *)node->obj)->normal = vec_unit(string_to_vec(argv[2]));
	((t_cylinder *)node->obj)->diameter = ft_atod(argv[3]);
	if (((t_cylinder *)node->obj)->diameter <= 0)
		error_exit("Error\nObject argument error\n");
	((t_cylinder *)node->obj)->height = ft_atod(argv[4]);
	if (((t_cylinder *)node->obj)->height <= 0)
		error_exit("Error\nObject argument error\n");
	check_color_pattern(mlx_arg, &((t_cylinder *)node->obj)->surface, argv[5]);
	((t_cylinder *)node->obj)->surface.mat = get_material_type(argv[6]);
}

void	add_cone(t_mlx_arg *mlx_arg, char **argv)
{
	t_obj_list	*node;

	if (get_argv_size(argv) <= 5)
		error_exit("Error\nObject argument error\n");
	node = add_object(mlx_arg, OBJ_CONE);
	node->obj = ft_calloc(1, sizeof(t_cone));
	if (node->obj == NULL)
		error_exit("Error\nmalloc fail\n");
	((t_cone *)node->obj)->center = string_to_vec(argv[1]);
	((t_cone *)node->obj)->normal = vec_unit(string_to_vec(argv[2]));
	((t_cone *)node->obj)->cosine = ft_atod(argv[3]);
	if (((t_cone *)node->obj)->cosine < -1 || ((t_cone *)node->obj)->cosine > 1)
		error_exit("Error\nObject argument error\n");
	((t_cone *)node->obj)->height = ft_atod(argv[4]);
	if (((t_cone *)node->obj)->height == 0)
		error_exit("Error\nObject argument error\n");
	check_color_pattern(mlx_arg, &((t_cone *)node->obj)->surface, argv[5]);
	((t_cone *)node->obj)->surface.mat = get_material_type(argv[6]);
}
