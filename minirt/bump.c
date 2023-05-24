/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bump.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mingkang <mingkang@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 13:06:08 by mingkang          #+#    #+#             */
/*   Updated: 2023/03/08 15:35:15 by mingkang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static t_vec	calc_bump_normal(t_texture bump, int x, int y)
{
	double		color;
	double		du;
	double		dv;

	color = (double)get_r(get_pixel(bump, x, y)) / 255;
	if (x == 0)
		du = ((double)get_r(get_pixel(bump, x + 1, y)) / 255) - color;
	else if (x == bump.width)
		du = color - ((double)get_r(get_pixel(bump, x - 1, y)) / 255);
	else
		du = ((double)get_r(get_pixel(bump, x + 1, y)) / 255) - \
			((double)get_r(get_pixel(bump, x - 1, y)) / 255);
	if (y == 0)
		dv = ((double)get_r(get_pixel(bump, x, y + 1)) / 255) - color;
	else if (y == bump.height)
		dv = color - ((double)get_r(get_pixel(bump, x, y - 1)) / 255);
	else
		dv = ((double)get_r(get_pixel(bump, x, y + 1)) / 255) - \
			((double)get_r(get_pixel(bump, x, y - 1)) / 255);
	return (vec_unit(vec(du, dv, 1.0)));
}

void	set_normal(t_hit_record *rec, int x, int y)
{
	t_vec		tangent;
	t_vec		bitangent;
	t_vec		tmp;
	t_vec		out;

	tangent = vec_unit(vec_cross(vec(0, 1, 0), rec->normal));
	if (vec_cmp(tangent, vec(0, 0, 0)) == 0)
		tangent = vec(1, 0, 0);
	bitangent = vec_cross(tangent, rec->normal);
	tmp = calc_bump_normal(rec->surface.bump, x, y);
	out.x = tangent.x * tmp.x + bitangent.x * tmp.y + rec->normal.x * tmp.z;
	out.y = tangent.y * tmp.x + bitangent.y * tmp.y + rec->normal.y * tmp.z;
	out.z = tangent.z * tmp.x + bitangent.z * tmp.y + rec->normal.z * tmp.z;
	rec->normal = out;
}
