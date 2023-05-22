/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 11:32:58 by jpark2            #+#    #+#             */
/*   Updated: 2023/03/08 15:58:18 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

static void	set_texture(t_mlx_arg *mlx_arg, t_texture *texture, char *filename)
{
	texture->img = NULL;
	texture->addr = NULL;
	texture->img = mlx_xpm_file_to_image(mlx_arg->mlx, filename, \
								&texture->width, &texture->height);
	if (texture->img == NULL)
		error_exit("Error\nxpm file name is wrong\n");
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp, \
								&texture->size_line, &texture->endn);
	if (texture->addr == NULL)
		error_exit("Error\nxpm file name is wrong\n");
}

static char	*remove_newline(char *s)
{
	char	*ret;
	char	*temp;

	temp = ft_strchr(s, '\n');
	if (temp == NULL)
		return (s);
	ret = malloc(sizeof(char) * (temp - s + 1));
	if (ret == NULL)
		error_exit("Error\nmalloc fail\n");
	ft_strlcpy(ret, s, temp - s + 1);
	free(s);
	return (ret);
}

t_vec	check_texture(double u, double v)
{
	if (((int)(u * 10) + (int)(v * 10)) % 2 == 0)
		return (vec(0.2, 0.3, 0.1));
	return (vec(0.9, 0.9, 0.9));
}

void	check_color_pattern(t_mlx_arg *mlx_arg, t_surface *surf, char *s)
{
	char	**color;
	int		size;

	color = ft_split(s, ',');
	size = get_argv_size(color);
	if (size == 1 && ft_strcmp(color[0], "checker\n") == 0)
		surf->color = vec((double)-1.0000, (double)-1.0000, (double)-1.0000);
	else if ((size == 1 || size == 2) && ft_isalpha(color[0][0]) == 1)
	{
		surf->color = vec((double)-2.0000, (double)-2.0000, (double)-2.0000);
		color[0] = remove_newline(color[0]);
		set_texture(mlx_arg, &surf->texture, color[0]);
		if (size == 2 && ft_isalpha(color[1][0]) == 1)
		{
			color[1] = remove_newline(color[1]);
			set_texture(mlx_arg, &surf->bump, color[1]);
		}
	}
	else if (size == 3)
		surf->color = vec(color_resize((double)ft_error_atoi(color[0]) / 255), \
						color_resize((double)ft_error_atoi(color[1]) / 255), \
						color_resize((double)ft_error_atoi(color[2]) / 255));
	else
		error_exit("Error\nObject argument error\n");
	argv_free(color);
}

t_vec	get_texture(t_hit_record *rec, double u, double v)
{
	int			x;
	int			y;
	int			color;
	t_vec		out;

	x = (int)((1 - u) * rec->surface.texture.width);
	y = (int)((1 - v) * rec->surface.texture.height);
	color = get_pixel(rec->surface.texture, x, y);
	out = vec((double)get_r(color) / 255, (double)get_g(color) / 255, \
				(double)get_b(color) / 255);
	if (rec->surface.bump.img != NULL && rec->surface.bump.bpp != 0)
		set_normal(rec, x, y);
	return (out);
}
