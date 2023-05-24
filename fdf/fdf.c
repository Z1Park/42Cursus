/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 10:18:30 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/05 20:48:38 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	close_window(void)
{
	exit(EXIT_SUCCESS);
	return (0);
}

static void	set_params(t_hook_var *hook_var, char *filename)
{
	hook_var->map = file_parsing(filename);
	hook_var->cod = make_coordinate(hook_var->map);
	map_to_coordinate(hook_var->map, hook_var->cod);
	hook_var->origin = malloc(sizeof(t_cod_2d));
	if (hook_var->origin == NULL)
		print_error(ERR_ALLOC_FAIL, NULL);
	hook_var->origin->x = MAX_WIDTH / 2;
	hook_var->origin->y = MAX_HEIGHT - AREA_MARGIN;
	hook_var->origin->color = 0;
	hook_var->var = init_and_set_window(hook_var->map);
	hook_var->yaw_angle = 0;
	hook_var->pitch_angle = 0;
	hook_var->roll_angle = 0;
}

int	main(int ac, char **av)
{
	t_hook_var	hook_var;

	if (ac != 2)
		print_error(ERR_WRONG_INPUT, NULL);
	set_params(&hook_var, av[1]);
	set_images(&hook_var);
	draw_map(hook_var.map, hook_var.var, hook_var.cod, hook_var.origin);
	mlx_key_hook(hook_var.var->win, hook_control, &hook_var);
	mlx_hook(hook_var.var->win, 17, 1L << 15, close_window, NULL);
	mlx_loop(hook_var.var->mlx);
}
