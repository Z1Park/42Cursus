/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingkang <mingkang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/07 19:12:54 by mingkang          #+#    #+#             */
/*   Updated: 2023/03/07 19:42:37 by mingkang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_r(int trgb)
{
	return ((trgb >> 16) & 0xFF);
}

int	get_g(int trgb)
{
	return ((trgb >> 8) & 0xFF);
}

int	get_b(int trgb)
{
	return (trgb & 0xFF);
}

unsigned int	get_pixel(t_texture texture, int x, int y)
{
	unsigned int	color;

	color = *(unsigned int *)(texture.addr + \
			(y * texture.size_line + x * (texture.bpp / 8)));
	return (color);
}

void	put_pixel(t_mlx_arg *mlx_arg, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < mlx_arg->cam.img_width && \
		y >= 0 && y < mlx_arg->cam.img_height)
	{
		dst = mlx_arg->addr + (y * mlx_arg->size_line + x * (mlx_arg->bpp / 8));
		*(unsigned int *)dst = color;
	}
}
