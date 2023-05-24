/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/04 12:43:26 by jpark2            #+#    #+#             */
/*   Updated: 2023/03/09 12:31:39 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_filename(char *filename)
{
	size_t	len;

	len = ft_strlen(filename);
	if (len <= 3)
		return (-1);
	if (ft_strcmp(filename + len - 3, ".rt") != 0)
		return (-1);
	return (0);
}

static void	mlx_varables_set(t_mlx_arg *mlx_arg)
{
	mlx_arg->mlx = mlx_init();
	if (mlx_arg->mlx == NULL)
		error_exit("Error\nmlx initialize fail\n");
	mlx_arg->win = mlx_new_window(mlx_arg->mlx, mlx_arg->cam.img_width, \
			mlx_arg->cam.img_height, "minirt");
	if (mlx_arg->win == NULL)
		error_exit("Error\nmlx window initialize fail\n");
	mlx_arg->img = mlx_new_image(mlx_arg->mlx, mlx_arg->cam.img_width, \
									mlx_arg->cam.img_height);
	if (mlx_arg->img == NULL)
		error_exit("Error\nimage creation fail\n");
	mlx_arg->addr = mlx_get_data_addr(mlx_arg->img, \
		&(mlx_arg->bpp), &(mlx_arg->size_line), &(mlx_arg->endn));
	if (mlx_arg->addr == NULL)
		error_exit("Error\nimage creation fail\n");
}

void	argument_init(t_mlx_arg *mlx_arg)
{
	ft_memset(&mlx_arg->cam, 0, sizeof(t_camera));
	mlx_arg->cam.aspect_ratio = 4.0 / 3.0;
	mlx_arg->cam.img_width = 1000;
	mlx_arg->cam.img_height = \
			(int)((double)mlx_arg->cam.img_width / mlx_arg->cam.aspect_ratio);
	mlx_varables_set(mlx_arg);
	mlx_arg->parse_flag = 0;
	mlx_arg->ambient = (t_vec){0, 0, 0};
	mlx_arg->ref_type = REFLECT_FULL_PHONG;
	mlx_arg->ray.dir = (t_vec){0, 0, 0};
	mlx_arg->ray.org = (t_vec){0, 0, 0};
	mlx_arg->background.color = vec(0.4, 0.5, 0.9);
	mlx_arg->background.texture.img = NULL;
	mlx_arg->background.texture.addr = NULL;
	mlx_arg->background.bump.img = NULL;
	mlx_arg->background.bump.addr = NULL;
	mlx_arg->lights = NULL;
	mlx_arg->obj_list = NULL;
}

static void	line_parse(t_mlx_arg *mlx_arg, char **argv)
{
	if (argv[0] == NULL)
		error_exit("Error\nfile parse error\n");
	if (get_argv_size(argv) == 1 && ft_strcmp(argv[0], "\n") == 0)
		return ;
	if (ft_strcmp(argv[0], "RF") == 0)
		set_reflection_type(mlx_arg, argv);
	else if (ft_strcmp(argv[0], "A") == 0)
		set_ambient(mlx_arg, argv);
	else if (ft_strcmp(argv[0], "C") == 0)
		set_camera(mlx_arg, argv);
	else if (ft_strcmp(argv[0], "L") == 0)
		add_light(mlx_arg, argv);
	else if (ft_strcmp(argv[0], "BG") == 0)
		add_background(mlx_arg, argv);
	else if (ft_strcmp(argv[0], "pl") == 0)
		add_plane(mlx_arg, argv);
	else if (ft_strcmp(argv[0], "sp") == 0)
		add_sphere(mlx_arg, argv);
	else if (ft_strcmp(argv[0], "cy") == 0)
		add_cylinder(mlx_arg, argv);
	else if (ft_strcmp(argv[0], "cn") == 0)
		add_cone(mlx_arg, argv);
	else
		error_exit("Error\nfile is wrong\n");
}

void	file_parse(t_mlx_arg *mlx_arg, char *filename)
{
	int		fd;
	char	*line;
	char	**line_split;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Error\ncan't find the file\n");
	line = get_next_line(fd);
	while (line != NULL)
	{
		line_split = ft_split(line, '\t');
		if (line_split == NULL)
			error_exit("Error\nmalloc fail\n");
		line_parse(mlx_arg, line_split);
		argv_free(line_split);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
