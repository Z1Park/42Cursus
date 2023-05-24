/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 16:52:49 by mingkang          #+#    #+#             */
/*   Updated: 2023/03/08 15:59:03 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static int	exit_hook(void *vars)
{
	t_mlx_arg	*mlx_arg;

	mlx_arg = (t_mlx_arg *)vars;
	mlx_destroy_image(mlx_arg->mlx, mlx_arg->img);
	write(1, "\033[0;94m|quit miniRT|\n\033[0;0m", 27);
	exit(EXIT_SUCCESS);
}

static int	key_press(int keycode, void *vars)
{
	t_mlx_arg			*mlx_arg;

	mlx_arg = (t_mlx_arg *)vars;
	if (keycode == K_ESC)
		exit_hook(vars);
	return (0);
}

void	cntl_map(t_mlx_arg *mlx_arg)
{
	mlx_hook(mlx_arg->win, ON_DESTROY, 0, exit_hook, mlx_arg);
	mlx_hook(mlx_arg->win, ON_KEYDOWN, 0, key_press, mlx_arg);
}
