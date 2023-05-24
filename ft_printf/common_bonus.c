/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 09:31:02 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/16 15:07:37 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	get_max(int a, int b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}

int	get_min(int a, int b)
{
	if (a >= b)
		return (b);
	else
		return (a);
}

size_t	get_pos(t_flag_info f_info, size_t buff, char *dst, size_t len)
{
	size_t	pos;

	if (f_info.flags & LEFT)
	{
		left_align(f_info, dst, len);
		pos = 0;
	}
	else
	{
		right_align(f_info, buff, dst, len);
		pos = buff - len - 1;
	}
	return (pos);
}

void	right_align(t_flag_info f_info, size_t buff, char *dst, size_t len)
{
	size_t	pos;

	pos = buff;
	if (f_info.flags & ZERO_PAD && ((f_info.flags & PRECISION) == 0))
		pos = 0;
	else if (f_info.width >= len && f_info.prec >= len)
	{
		if (f_info.width >= f_info.prec)
			pos = f_info.width - f_info.prec;
		else
			pos = 0;
	}
	else if (f_info.width >= len && f_info.prec < len)
		pos = f_info.width;
	else if (f_info.width < len && f_info.prec >= len)
		pos = 0;
	else if (f_info.width < len && f_info.prec < len)
		pos = len;
	while (pos < buff - 1)
		dst[pos++] = '0';
}

void	left_align(t_flag_info f_info, char *dst, size_t len)
{
	size_t	pos;
	size_t	end;

	pos = 0;
	end = len;
	if (f_info.prec > len)
		end = f_info.prec;
	else if (f_info.width > len)
		end = len;
	else
		end = 0;
	if (f_info.flags & SIGN || f_info.flags & BLANK)
		pos++;
	while (pos < end)
		dst[pos++] = '0';
}
