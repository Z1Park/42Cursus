/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_int_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 13:52:14 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/16 18:27:21 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static size_t	make_sign(t_flag_info f_info, size_t b_len, char *dst, char *s)
{
	size_t	pos;

	pos = get_pos(f_info, b_len, dst, ft_strlen(s));
	if (*s == '-' || *s == ' ' || *s == '+')
	{
		if (f_info.flags & LEFT)
				dst[pos++] = *(s++);
		else
		{
			if (f_info.flags & ZERO_PAD && (f_info.flags & PRECISION) == 0)
				dst[0] = *(s++);
			else if (f_info.flags & PRECISION && f_info.prec > ft_strlen(s))
				dst[b_len - f_info.prec - 2] = *(s++);
			else
				dst[pos] = *(s++);
			pos++;
		}
	}
	return (pos);
}

static void	make_int(t_flag_info f_info, size_t buff_len, char *dst, char *s)
{
	size_t	pos;
	size_t	s_len;

	pos = 0;
	while (pos < buff_len - 1)
		dst[pos++] = ' ';
	s_len = ft_strlen(s);
	pos = make_sign(f_info, buff_len, dst, s);
	if (*s == ' ' || *s == '+' || *s == '-')
		s++;
	while (*s != 0 && pos < buff_len - 1)
		dst[pos++] = *(s++);
}

static char	check_int_zero(t_flag_info f_info, t_list *lst, int buff, int d)
{
	size_t	i;

	if (f_info.flags & PRECISION && f_info.prec == 0 && d == 0)
	{
		if (f_info.width == 0)
			buff = 1 + ((f_info.flags & 0x60) != 0);
		else if (f_info.width == 1)
			buff = 2;
		free(lst->str);
		lst->str = malloc(sizeof(char) * buff);
		if (lst->str == NULL)
		{
			lst->s_len = -1;
			return (0);
		}
		i = 0;
		while ((int)i < buff - 1)
			lst->str[i++] = ' ';
		if (f_info.flags & SIGN)
			lst->str[((f_info.flags & LEFT) == 0) * (buff - 2)] = '+';
		lst->str[buff - 1] = 0;
		lst->s_len = buff - 1;
		return (0);
	}
	return (1);
}

int	flag_to_int(t_list *lst, int d)
{
	t_flag_info	f_info;
	int			buff_size;
	char		*s;

	f_info = get_flags(lst->str, lst->s_len);
	s = ft_itoa(d, f_info.flags, f_info.prec);
	if (s == NULL)
		return (-1);
	buff_size = get_buffer_size(f_info, lst->type, ft_strlen(s)) + 1;
	if (check_int_zero(f_info, lst, buff_size, d) == 1 && buff_size != -1)
	{
		free(lst->str);
		lst->str = malloc(sizeof(char) * buff_size);
		if (lst->str == NULL)
		{
			free(s);
			return (-1);
		}
		lst->str[buff_size - 1] = 0;
		make_int(f_info, buff_size, lst->str, s);
		lst->s_len = buff_size - 1;
	}
	free(s);
	return (lst->s_len);
}
