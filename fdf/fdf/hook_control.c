/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_control.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:55:53 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/05 19:27:46 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	rotation(int keycode, t_hook_var *vars)
{
	mlx_put_image_to_window(vars->var->mlx, vars->var->win, \
		vars->black_screen->img, 0, 0);
	if (keycode == KEY_J)
		yaw_rotate(vars, 30);
	else if (keycode == KEY_U)
		yaw_rotate(vars, -30);
	else if (keycode == KEY_K)
		roll_rotate(vars, -30);
	else if (keycode == KEY_I)
		roll_rotate(vars, 30);
	else if (keycode == KEY_L)
		pitch_rotate(vars, 30);
	else
		pitch_rotate(vars, -30);
	draw_map(vars->map, vars->var, vars->cod, vars->origin);
}

static void	move(int keycode, t_hook_var *vars)
{
	if (keycode == KEY_RIGHT)
		vars->origin->x += 50;
	else if (keycode == KEY_LEFT)
		vars->origin->x -= 50;
	else if (keycode == KEY_UP)
		vars->origin->y -= 50;
	else if (keycode == KEY_DOWN)
		vars->origin->y += 50;
	mlx_put_image_to_window(vars->var->mlx, vars->var->win, \
		vars->black_screen->img, 0, 0);
	draw_map(vars->map, vars->var, vars->cod, vars->origin);
}

static void	zoom_in_zoom_out(int keycode, t_hook_var *vars)
{
	if (keycode == KEY_PLUS)
		vars->map->gap_pixel += 2;
	else if (keycode == KEY_MINUS)
	{
		if (vars->map->gap_pixel > 3)
			vars->map->gap_pixel -= 2;
	}
	mlx_put_image_to_window(vars->var->mlx, vars->var->win, \
		vars->black_screen->img, 0, 0);
	draw_map(vars->map, vars->var, vars->cod, vars->origin);
}

static void	change_projection(int keycode, t_hook_var *vars)
{
	mlx_put_image_to_window(vars->var->mlx, vars->var->win, \
		vars->black_screen->img, 0, 0);
	if (keycode == KEY_7)
		mlx_put_image_to_window(vars->var->mlx, vars->var->win, \
			vars->para_front->img, 0, 0);
	else if (keycode == KEY_8)
		mlx_put_image_to_window(vars->var->mlx, vars->var->win, \
			vars->para_side->img, 0, 0);
	else if (keycode == KEY_9)
		mlx_put_image_to_window(vars->var->mlx, vars->var->win, \
			vars->para_top->img, 0, 0);
	else
		draw_map(vars->map, vars->var, vars->cod, vars->origin);
}

int	hook_control(int keycode, t_hook_var *vars)
{
	if (keycode == KEY_ESC)
	{
		mlx_destroy_window(vars->var->mlx, vars->var->win);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == KEY_J || keycode == KEY_L \
		|| keycode == KEY_I || keycode == KEY_K \
		|| keycode == KEY_U || keycode == KEY_O)
		rotation(keycode, vars);
	else if (keycode == KEY_LEFT || keycode == KEY_RIGHT \
		|| keycode == KEY_UP || keycode == KEY_DOWN)
		move(keycode, vars);
	else if (keycode == KEY_PLUS || keycode == KEY_MINUS)
		zoom_in_zoom_out(keycode, vars);
	else if (keycode == KEY_7 || keycode == KEY_8 \
		|| keycode == KEY_9 || keycode == KEY_0)
		change_projection(keycode, vars);
	return (0);
}
