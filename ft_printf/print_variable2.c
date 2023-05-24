/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_variable2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:15:47 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/15 12:30:22 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	get_hex_len(unsigned long long x)
{
	size_t	len;

	len = 0;
	if (x == 0)
		len = 1;
	while (x != 0)
	{
		x /= 16;
		len++;
	}
	return (len);
}

int	flag_to_int(t_list *lst, int d)
{
	free(lst->str);
	lst->str = ft_itoa(d, 0, 0);
	if (lst->str == 0)
		return (-1);
	lst->s_len = ft_strlen(lst->str);
	return (lst->s_len);
}

int	flag_to_uint(t_list *lst, unsigned int u)
{
	free(lst->str);
	lst->str = ft_uitoa(u, 0);
	if (lst->str == 0)
		return (-1);
	lst->s_len = ft_strlen(lst->str);
	return (lst->s_len);
}

int	flag_to_hex(t_list *lst, unsigned int x)
{
	char			*hex;
	size_t			len;

	len = get_hex_len((unsigned long long)x);
	free(lst->str);
	lst->str = malloc(sizeof(char) * (len + 1));
	if (lst->str == 0)
		return (-1);
	if (lst->type == T_LHEX)
		hex = "0123456789abcdef";
	else
		hex = "0123456789ABCDEF";
	lst->str[len] = 0;
	lst->s_len = len;
	if (x == 0)
		lst->str[0] = '0';
	while (x != 0)
	{
		lst->str[--len] = hex[x % 16];
		x /= 16;
	}
	return (lst->s_len);
}

int	flag_to_pcnt(t_list *lst)
{
	free(lst->str);
	lst->str = malloc(sizeof(char) * (2));
	if (lst->str == 0)
		return (-1);
	lst->str[0] = '%';
	lst->str[1] = 0;
	lst->s_len = 1;
	return (lst->s_len);
}
