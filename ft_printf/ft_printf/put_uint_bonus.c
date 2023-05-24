/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_uint_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 13:52:14 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/16 18:28:09 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	make_uint(t_flag_info f_info, size_t buff_len, char *dst, char *s)
{
	size_t	pos;

	pos = 0;
	while (pos < buff_len - 1)
		dst[pos++] = ' ';
	pos = get_pos(f_info, buff_len, dst, ft_strlen(s));
	while (*s != 0 && pos < buff_len - 1)
		dst[pos++] = *(s++);
}

char	check_uint_zero(t_flag_info f_info, t_list *lst, \
	int buff, unsigned int d)
{
	size_t	i;

	if (f_info.flags & PRECISION && f_info.prec == 0 && d == 0)
	{
		if (f_info.width == 0)
			buff = 1;
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
		lst->str[buff - 1] = 0;
		lst->s_len = buff - 1;
		return (0);
	}
	return (1);
}

int	flag_to_uint(t_list *lst, unsigned int u)
{
	t_flag_info	f_info;
	int			buff_size;
	char		*s;

	f_info = get_flags(lst->str, lst->s_len);
	s = ft_uitoa(u, f_info.prec);
	if (s == 0)
		return (-1);
	buff_size = get_buffer_size(f_info, lst->type, ft_strlen(s)) + 1;
	if (check_uint_zero(f_info, lst, buff_size, u) == 1 && buff_size != -1)
	{
		free(lst->str);
		lst->str = malloc(sizeof(char) * buff_size);
		if (lst->str == NULL)
		{
			free(s);
			return (-1);
		}
		make_uint(f_info, buff_size, lst->str, s);
		lst->s_len = buff_size - 1;
	}
	free(s);
	return (lst->s_len);
}
