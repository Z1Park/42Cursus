/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_char_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 14:56:10 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/16 18:14:43 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	make_char(t_flag_info f_info, size_t buff_len, char *dst, char c)
{
	size_t	i;
	size_t	pos;

	i = 0;
	while (i < buff_len)
		dst[i++] = ' ';
	if (f_info.flags & LEFT)
		pos = 0;
	else
		pos = buff_len - 1;
	dst[pos] = c;
}

int	flag_to_char(t_list *lst, char c)
{
	t_flag_info	f_info;
	int			buff_size;

	f_info = get_flags(lst->str, lst->s_len);
	buff_size = get_buffer_size(f_info, lst->type, 1) + 1;
	if (buff_size != -1)
	{
		free(lst->str);
		lst->str = malloc(sizeof(char) * buff_size);
		if (lst->str == 0)
			return (-1);
		lst->str[buff_size - 1] = 0;
		make_char(f_info, buff_size - 1, lst->str, c);
		lst->s_len = buff_size - 1;
	}	
	return (lst->s_len);
}
