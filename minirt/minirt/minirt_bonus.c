/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 11:01:10 by jpark2            #+#    #+#             */
/*   Updated: 2023/03/08 15:59:00 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	free_objects(t_mlx_arg *mlx_arg, t_obj_list *list)
{
	t_obj_list	*temp;
	t_surface	*surf;

	temp = list;
	while (temp != NULL)
	{
		if (temp->obj_type == OBJ_SPHERE)
			surf = &(((t_sphere *)temp->obj)->surface);
		else if (temp->obj_type == OBJ_PLANE)
			surf = &(((t_plane *)temp->obj)->surface);
		else if (temp->obj_type == OBJ_CYLINDER)
			surf = &(((t_cylinder *)temp->obj)->surface);
		else if (temp->obj_type == OBJ_CONE)
			surf = &(((t_cone *)temp->obj)->surface);
		if (surf->texture.img != NULL)
			mlx_destroy_image(mlx_arg->mlx, surf->texture.img);
		if (surf->bump.img != NULL)
			mlx_destroy_image(mlx_arg->mlx, surf->bump.img);
		free(temp);
		temp = temp->next;
	}
}

void	free_argument(t_mlx_arg *mlx_arg)
{
	t_light	*temp;

	free_objects(mlx_arg, mlx_arg->obj_list);
	while (mlx_arg->lights != NULL)
	{
		temp = mlx_arg->lights->next;
		free(mlx_arg->lights);
		mlx_arg->lights = temp;
	}
	if (mlx_arg->background.texture.img != NULL)
		mlx_destroy_image(mlx_arg->mlx, mlx_arg->background.texture.img);
	if (mlx_arg->background.bump.img != NULL)
		mlx_destroy_image(mlx_arg->mlx, mlx_arg->background.bump.img);
	if (mlx_arg->img != NULL)
		mlx_destroy_image(mlx_arg->mlx, mlx_arg->img);
	if (mlx_arg->win != NULL)
		mlx_destroy_window(mlx_arg->mlx, mlx_arg->win);
}

void	error_exit(char *str)
{
	printf("%s\n", str);
	exit(EXIT_FAILURE);
}

int	main(int ac, char **av)
{
	t_mlx_arg	mlx_arg;

	if (ac != 2 || check_filename(av[1]) < 0)
		error_exit("Error\nusage: ./minirt <filename.rt>");
	argument_init(&mlx_arg);
	file_parse(&mlx_arg, av[1]);
	ray_casting(&mlx_arg);
	cntl_map(&mlx_arg);
	mlx_loop(mlx_arg.mlx);
	free_argument(&mlx_arg);
	return (EXIT_SUCCESS);
}
