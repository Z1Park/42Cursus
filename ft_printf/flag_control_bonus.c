/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_control_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 11:47:57 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/20 12:43:59 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static	char	check_front(char **str, int *len)
{
	char	flags;

	flags = 0;
	while (**str == '+' || **str == ' ' || **str == '#'
		|| **str == '-' || **str == '0')
	{
		if (**str == '+')
			flags |= SIGN;
		else if (**str == ' ' && (flags & SIGN) == 0)
			flags |= BLANK;
		else if (**str == '#')
			flags |= PREPEND;
		else if (**str == '-')
			flags |= LEFT;
		else if (**str == '0' && (flags & LEFT) == 0)
			flags |= ZERO_PAD;
		(*str)++;
		(*len)--;
	}
	if (flags & SIGN && flags & BLANK)
		flags &= 0xff ^ BLANK;
	if (flags & LEFT && flags & ZERO_PAD)
		flags &= 0xff ^ ZERO_PAD;
	return (flags);
}

t_flag_info	get_flags(char *str, int len)
{
	int			i;
	t_flag_info	f_info;

	i = 0;
	f_info.flags = check_front(&str, &len);
	f_info.width = 0;
	f_info.prec = 0;
	while (i < len && str[i] != '.')
	{
		f_info.flags |= WIDTH;
		if (f_info.width < 2147483647)
			f_info.width = f_info.width * 10 + str[i++] - '0';
	}
	if (str[i] == '.')
	{
		f_info.flags |= PRECISION;
		i++;
	}
	while (i < len)
	{
		if (f_info.prec <= 2147483649)
			f_info.prec = f_info.prec * 10 + str[i++] - '0';
	}
	return (f_info);
}

t_ftype	get_ftype(char c)
{
	t_ftype	type;

	if (c == 'c')
		type = T_CHAR;
	else if (c == 's')
		type = T_STR;
	else if (c == 'p')
		type = T_PTR;
	else if (c == 'd')
		type = T_INT;
	else if (c == 'i')
		type = T_INT;
	else if (c == 'u')
		type = T_UINT;
	else if (c == 'x')
		type = T_LHEX;
	else if (c == 'X')
		type = T_UHEX;
	else if (c == '%')
		type = T_PCNT;
	else
		type = T_NONE;
	return (type);
}

static int	str_buffer_size(t_flag_info f_info, size_t s_len)
{
	if (f_info.width < s_len)
	{
		if (f_info.flags & PRECISION)
		{
			if (f_info.width > f_info.prec)
				return (f_info.width);
			else
				return (get_min(f_info.prec, (int)s_len));
		}
		else
			return (s_len);
	}
	else
		return (f_info.width);
}

int	get_buffer_size(t_flag_info f_info, t_ftype type, size_t s_len)
{
	if (f_info.width >= 2147483647)
		return (-1);
	if (type == T_CHAR || type == T_PTR || type == T_PCNT)
		return (get_max(f_info.width, s_len));
	else if (type == T_STR)
		return (str_buffer_size(f_info, s_len));
	else
	{
		if ((f_info.flags & SIGN || f_info.flags & BLANK)
			&& f_info.prec > s_len && f_info.prec > f_info.width)
			f_info.prec++;
		return (get_max(get_max(f_info.width, f_info.prec), s_len));
	}
	return (0);
}
