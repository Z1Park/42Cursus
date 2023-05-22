/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_ptr_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 09:23:07 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/16 18:30:12 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static char	*get_address(unsigned long long address)
{
	unsigned long long	tmp;
	size_t				len;
	char				*ptr;
	const char			hex[] = "0123456789abcdef";

	tmp = address;
	len = 0;
	if (tmp == 0)
		len = 1;
	while (tmp != 0)
	{
		len++;
		tmp /= 16;
	}
	ptr = malloc(sizeof(char) * (len + 1));
	if (ptr == NULL)
		return (NULL);
	ptr[0] = '0';
	ptr[len] = 0;
	while (len-- > 0)
	{
		ptr[len] = hex[address % 16];
		address /= 16;
	}
	return (ptr);
}

static void	make_ptr(t_flag_info f_info, size_t buff_len, char *dst, char *addr)
{
	size_t	i;
	size_t	pos;

	i = 0;
	while (i < buff_len)
		dst[i++] = ' ';
	if (f_info.flags & LEFT)
		pos = 0;
	else
		pos = buff_len - ft_strlen(addr) - 3;
	dst[pos++] = '0';
	dst[pos++] = 'x';
	ft_strlcpy(&dst[pos], addr, buff_len - pos);
}

int	flag_to_ptr(t_list *lst, void *ptr)
{
	t_flag_info	f_info;
	int			buff_size;
	char		*address;

	f_info = get_flags(lst->str, lst->s_len);
	address = get_address((unsigned long long)ptr);
	if (address == NULL)
		return (-1);
	buff_size = get_buffer_size(f_info, lst->type, ft_strlen(address) + 2) + 1;
	lst->s_len = -1;
	if (buff_size != -1)
	{
		free(lst->str);
		lst->str = malloc(sizeof(char) * buff_size);
		if (lst->str == NULL)
		{
			free(address);
			return (-1);
		}
		make_ptr(f_info, buff_size, lst->str, address);
		lst->s_len = buff_size - 1;
		free(address);
	}
	return (lst->s_len);
}
