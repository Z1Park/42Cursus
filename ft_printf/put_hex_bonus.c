/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_hex_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/13 09:23:07 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/16 18:35:02 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static char	*get_hexptr(size_t *len, unsigned long long x, t_flag_info f_info)
{
	char				*ptr;
	unsigned long long	i;

	*len = 0;
	if (x == 0)
		*len = 1;
	else if (f_info.flags & PREPEND)
		*len += 2;
	i = x;
	while (i != 0)
	{
		(*len)++;
		i /= 16;
	}
	if (x != 0 && (f_info.flags & (PREPEND | PRECISION)) == 0x12)
		*len = get_max(f_info.prec + 2, *len);
	else if (f_info.prec > *len)
		*len = f_info.prec;
	ptr = malloc(sizeof(char) * (*len + 1));
	if (ptr == 0)
		return (0);
	while (i < *len)
		ptr[i++] = '0';
	ptr[*len] = 0;
	return (ptr);
}

static char	*get_hex(unsigned long long x, t_flag_info f_info, t_ftype type)
{
	size_t		len;
	char		*ptr;
	const char	*hex;

	ptr = get_hexptr(&len, x, f_info);
	if (ptr == 0)
		return (0);
	if (type == T_LHEX)
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	if (f_info.flags & PREPEND && x != 0)
		ptr[1] = hex[15] + ('x' - 'f');
	while (x != 0)
	{
		ptr[--len] = hex[x % 16];
		x /= 16;
	}
	while (len > 0 && ptr[len - 1] != hex[15] + ('x' - 'f'))
		ptr[--len] = '0';
	return (ptr);
}

static void	make_hex(t_flag_info f_info, size_t buff_len, char *dst, char *hex)
{
	size_t	i;
	size_t	pos;

	i = 0;
	while (i < buff_len)
		dst[i++] = ' ';
	pos = get_pos(f_info, buff_len, dst, ft_strlen(hex));
	if (f_info.flags & ZERO_PAD && (f_info.flags & PRECISION) == 0)
	{
		i = 0;
		while (i < pos)
			dst[i++] = '0';
		if ((*(hex + 1) == 'x' || *(hex + 1) == 'X') && f_info.flags & PREPEND
			&& (f_info.flags & LEFT || f_info.flags & ZERO_PAD))
		{
			dst[0] = *(hex++);
			dst[1] = *(hex++);
			pos += 2;
		}
	}
	while (*hex != 0 && pos < buff_len - 1)
		dst[pos++] = *(hex++);
	dst[buff_len - 1] = 0;
}

int	flag_to_hex(t_list *lst, unsigned int x)
{
	t_flag_info	f_info;
	int			buff_size;
	char		*hex;

	f_info = get_flags(lst->str, lst->s_len);
	hex = get_hex((unsigned long long)x, f_info, lst->type);
	if (hex == 0)
		return (-1);
	buff_size = get_buffer_size(f_info, lst->type, ft_strlen(hex)) + 1;
	if (check_uint_zero(f_info, lst, buff_size, x) == 1 && buff_size != -1)
	{
		free(lst->str);
		lst->str = malloc(sizeof(char) * buff_size);
		if (lst->str == NULL)
		{
			free(hex);
			return (-1);
		}
		make_hex(f_info, buff_size, lst->str, hex);
		lst->s_len = buff_size - 1;
	}
	free(hex);
	return (lst->s_len);
}
