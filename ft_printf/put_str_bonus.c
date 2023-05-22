/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_str_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 09:23:07 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/16 18:30:27 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	make_str(t_flag_info f_info, size_t buff_len, char *dst, char *s)
{
	size_t	i;
	size_t	pos;
	size_t	s_len;

	i = 0;
	if ((*s == 0 && (f_info.flags & WIDTH) == 0)
		|| ((f_info.flags & PRECISION) && f_info.prec == 0))
		s_len = 0;
	else if (f_info.flags & PRECISION)
		s_len = get_min(ft_strlen(s), f_info.prec);
	else
		s_len = ft_strlen(s);
	while (i < buff_len - 1)
		dst[i++] = ' ';
	if (f_info.flags & LEFT)
		pos = 0;
	else
		pos = buff_len - s_len - 1;
	i = 0;
	while (i < s_len)
		dst[pos + i++] = *(s++);
	dst[buff_len - 1] = 0;
}

static void	make_null_str(t_list *lst, t_flag_info f_info, int buff, char *s)
{
	size_t	i;
	size_t	prec;

	i = 0;
	while ((int)i < buff - 1)
		lst->str[i++] = ' ';
	if (f_info.flags & LEFT)
		i = 0;
	else if (f_info.flags & PRECISION
		&& (int)f_info.prec < 7 && buff > (int)f_info.prec)
		i = buff - f_info.prec - 1;
	else
		i = buff - 7;
	prec = f_info.prec;
	while (*s != 0 && (int)i < buff - 1
		&& ((f_info.flags & PRECISION) == 0 || prec > 0))
	{
		lst->str[i++] = *(s)++;
		if (f_info.flags & PRECISION)
			prec--;
	}
	lst->s_len = buff - 1;
	lst->str[buff - 1] = 0;
}

static char	null_check(t_list *lst, char *s, t_flag_info f_info)
{
	int		buff_size;

	if (s != NULL)
		return (1);
	free(lst->str);
	buff_size = get_buffer_size(f_info, lst->type, 6) + 1;
	lst->s_len = -1;
	if (buff_size > 1)
	{
		lst->str = malloc(sizeof(char) * buff_size);
		if (lst->str == NULL)
			return (0);
		make_null_str(lst, f_info, buff_size, "(null)");
	}
	else
	{
		lst->str = malloc(sizeof(char) * 1);
		if (lst->str == NULL)
			return (0);
		lst->str[0] = 0;
		lst->s_len = 0;
	}
	return (0);
}

int	flag_to_str(t_list *lst, char *s)
{
	t_flag_info	f_info;
	int			buff_size;

	f_info = get_flags(lst->str, lst->s_len);
	if (null_check(lst, s, f_info) == 0)
		return (lst->s_len);
	if ((*s == 0 && (f_info.flags & WIDTH) == 0)
		|| ((f_info.flags & PRECISION) && f_info.prec == 0))
		buff_size = f_info.width + 1;
	else
		buff_size = get_buffer_size(f_info, lst->type, ft_strlen(s)) + 1;
	lst->s_len = -1;
	if (buff_size != -1)
	{
		free(lst->str);
		lst->str = malloc(sizeof(char) * buff_size);
		if (lst->str == NULL)
			return (-1);
		make_str(f_info, buff_size, lst->str, s);
		lst->s_len = buff_size - 1;
	}
	return (lst->s_len);
}
