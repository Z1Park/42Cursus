/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_variable1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:06:49 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/16 17:23:39 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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

int	flag_to_char(t_list *lst, char c)
{
	free(lst->str);
	lst->str = malloc(sizeof(char) * 2);
	if (lst->str == 0)
		return (-1);
	lst->str[0] = c;
	lst->str[1] = 0;
	lst->s_len = 1;
	return (lst->s_len);
}

int	flag_to_str(t_list *lst, char *s)
{
	size_t	len;

	if (s == NULL)
	{
		free(lst->str);
		lst->str = ft_strdup("(null)", 7);
		lst->s_len = 6;
		return (6);
	}
	len = ft_strlen(s);
	free(lst->str);
	lst->str = malloc(sizeof(char) * (len + 1));
	if (lst->str == NULL)
		return (-1);
	ft_strlcpy(lst->str, s, len + 1);
	lst->s_len = len;
	return (len);
}

int	flag_to_ptr(t_list *lst, void *ptr)
{
	size_t				len;
	const char			*hex = "0123456789abcdef";
	unsigned long long	addr;

	free(lst->str);
	if (ptr == NULL)
		len = 3;
	else
		len = get_hex_len((unsigned long long)ptr) + 2;
	lst->str = malloc(sizeof(char) * (len + 1));
	if (lst->str == 0)
		return (-1);
	lst->s_len = len;
	lst->str[0] = '0';
	lst->str[1] = 'x';
	lst->str[2] = '0';
	lst->str[len] = 0;
	addr = (unsigned long long)ptr;
	while (addr != 0)
	{
		lst->str[--len] = hex[addr % 16];
		addr /= 16;
	}
	return (lst->s_len);
}
