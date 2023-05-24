/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 19:27:52 by jpark2            #+#    #+#             */
/*   Updated: 2023/03/09 11:12:27 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_ambient(t_mlx_arg *mlx_arg, char **argv)
{
	char	**color;

	if (get_argv_size(argv) <= 2 || (mlx_arg->parse_flag & PARSE_AMBIENT))
		error_exit("Error\nObject argument error\n");
	mlx_arg->parse_flag |= PARSE_AMBIENT;
	color = ft_split(argv[2], ',');
	if (get_argv_size(color) != 3)
		error_exit("Error\nObject argument error\n");
	mlx_arg->ambient = \
		vec_mul(vec((double)ft_error_atoi(color[0]) / 255, \
					(double)ft_error_atoi(color[1]) / 255, \
					(double)ft_error_atoi(color[2]) / 255), ft_atod(argv[1]));
	argv_free(color);
}

void	add_background(t_mlx_arg *mlx_arg, char **argv)
{
	if (get_argv_size(argv) <= 1 || (mlx_arg->parse_flag & PARSE_BACKGROUND))
		error_exit("Error\nObject argument error\n");
	mlx_arg->parse_flag |= PARSE_BACKGROUND;
	if (mlx_arg->ref_type != REFLECT_RAY_TRACING)
		check_color_pattern(mlx_arg, &mlx_arg->background, argv[1]);
}

void	set_camera(t_mlx_arg *mlx_arg, char **argv)
{
	t_camera	*cam;
	t_vec		lookat;
	double		focus_dist;

	if (get_argv_size(argv) <= 3 || (mlx_arg->parse_flag & PARSE_CAMERA))
		error_exit("Error\nObject argument error\n");
	mlx_arg->parse_flag |= PARSE_CAMERA;
	cam = &mlx_arg->cam;
	cam->theta = degrees_to_radians(ft_atod(argv[3]));
	cam->viewport_width = 2.0 * tan(cam->theta / 2);
	cam->viewport_height = cam->viewport_width / cam->aspect_ratio;
	cam->origin = string_to_vec(argv[1]);
	lookat = string_to_vec(argv[2]);
	focus_dist = vec_scalar(vec_diff(cam->origin, lookat));
	cam->w = vec_unit(vec_diff(cam->origin, lookat));
	cam->u = vec_unit(vec_cross(vec(0, 0, 1), cam->w));
	if (vec_cmp(cam->u, vec(0, 0, 0)) == 0)
		cam->u = vec(1, 0, 0);
	cam->v = vec_cross(cam->w, cam->u);
	cam->horizon = vec_mul(cam->u, cam->viewport_width * focus_dist);
	cam->vert = vec_mul(cam->v, cam->viewport_height * focus_dist);
	cam->left_bot = vec_diff(vec_diff(vec_diff(cam->origin, \
		vec_div(cam->horizon, 2.0)), vec_div(cam->vert, 2.0)), \
		vec_mul(cam->w, focus_dist));
	cam->lens_radius = 0.05;
}

void	set_reflection_type(t_mlx_arg *mlx_arg, char **argv)
{
	if (get_argv_size(argv) <= 1 || (mlx_arg->parse_flag & PARSE_REFLECTION))
		error_exit("Error\nObject argument error\n");
	mlx_arg->parse_flag |= PARSE_REFLECTION;
	if (ft_strcmp(argv[1], "phong\n") == 0)
		mlx_arg->ref_type = REFLECT_PHONG;
	else if (ft_strcmp(argv[1], "full_phong\n") == 0)
		mlx_arg->ref_type = REFLECT_FULL_PHONG;
	else if (ft_strcmp(argv[1], "ray_tracing\n") == 0)
		mlx_arg->ref_type = REFLECT_RAY_TRACING;
	else
		error_exit("Error\nObject argument error\n");
}
