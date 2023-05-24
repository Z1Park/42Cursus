/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 21:08:44 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/04 21:28:42 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	yaw_rotate(t_hook_var *var, double angle)
{
	double	theta;
	int		i;
	int		j;
	double	x;
	double	y;

	theta = angle * M_PI / 180;
	i = 0;
	while (i < var->map->height)
	{
		j = 0;
		while (j < var->map->width)
		{
			x = var->cod[i][j].x;
			y = var->cod[i][j].y;
			var->cod[i][j].x = x * cos(theta) - y * sin(theta);
			var->cod[i][j].y = x * sin(theta) + y * cos(theta);
			j++;
		}
		i++;
	}
	var->yaw_angle += angle;
}

void	pitch_rotate(t_hook_var *var, double angle)
{
	double	theta;
	int		i;
	int		j;
	double	x;
	double	z;

	theta = angle * M_PI / 180;
	i = 0;
	while (i < var->map->height)
	{
		j = 0;
		while (j < var->map->width)
		{
			x = var->cod[i][j].x;
			z = var->cod[i][j].z;
			var->cod[i][j].x = x * cos(theta) - z * sin(theta);
			var->cod[i][j].z = x * sin(theta) + z * cos(theta);
			j++;
		}
		i++;
	}
	var->pitch_angle += angle;
}

void	roll_rotate(t_hook_var *var, double angle)
{
	double	theta;
	int		i;
	int		j;
	double	y;
	double	z;

	theta = angle * M_PI / 180;
	i = 0;
	while (i < var->map->height)
	{
		j = 0;
		while (j < var->map->width)
		{
			y = var->cod[i][j].y;
			z = var->cod[i][j].z;
			var->cod[i][j].y = y * cos(theta) - z * sin(theta);
			var->cod[i][j].z = y * sin(theta) + z * cos(theta);
			j++;
		}
		i++;
	}
	var->roll_angle += angle;
}
