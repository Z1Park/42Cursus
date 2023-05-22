/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_pcnt_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:16:50 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/16 18:29:34 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	make_pcnt(t_flag_info f_info, size_t buff_len, char *dst)
{
	size_t	pos;

	pos = 0;
	while (pos < buff_len)
		dst[pos++] = ' ';
	if (f_info.flags & LEFT)
		pos = 0;
	else
	{
		if (f_info.flags & ZERO_PAD)
		{
			pos = 0;
			while (pos < buff_len)
				dst[pos++] = '0';
		}
		pos = buff_len - 1;
	}
	dst[pos] = '%';
}

int	flag_to_pcnt(t_list *lst)
{
	t_flag_info	f_info;
	int			buff_size;

	f_info = get_flags(lst->str, lst->s_len);
	buff_size = get_buffer_size(f_info, lst->type, 1) + 1;
	lst->s_len = -1;
	if (buff_size != -1)
	{
		free(lst->str);
		lst->str = malloc(sizeof(char) * buff_size);
		if (lst->str == 0)
			return (-1);
		lst->str[buff_size - 1] = 0;
		make_pcnt(f_info, buff_size - 1, lst->str);
		lst->s_len = buff_size - 1;
	}	
	return (lst->s_len);
}
