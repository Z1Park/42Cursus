/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 11:37:36 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/16 17:25:36 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include "ft_printf.h"

static int	flag_convert(t_list *lst, va_list ap)
{
	int		i;

	i = 0;
	if (lst->type == T_CHAR)
		i = flag_to_char(lst, (char)va_arg(ap, int));
	else if (lst->type == T_STR)
		i = flag_to_str(lst, va_arg(ap, char *));
	else if (lst->type == T_PTR)
		i = flag_to_ptr(lst, va_arg(ap, void *));
	else if (lst->type == T_INT)
		i = flag_to_int(lst, va_arg(ap, int));
	else if (lst->type == T_UINT)
		i = flag_to_uint(lst, va_arg(ap, unsigned int));
	else if (lst->type == T_LHEX || lst->type == T_UHEX)
		i = flag_to_hex(lst, va_arg(ap, unsigned int));
	else if (lst->type == T_PCNT)
		i = flag_to_pcnt(lst);
	return (i);
}

static int	count_len(t_list *lst, va_list ap)
{
	int	len;
	int	tmp;

	len = 0;
	while (lst != 0)
	{
		if (lst->type == T_NONE)
			tmp = lst->s_len;
		else
			tmp = flag_convert(lst, ap);
		if (tmp == -1)
			return (-1);
		len += tmp;
		lst = lst->next;
	}
	return (len);
}

int	ft_printf(const char *s, ...)
{
	va_list	ap;
	t_list	*lst;
	int		prt_byt;

	prt_byt = 0;
	if (*s == 0)
		return (0);
	lst = make_lst(s, 0);
	if (lst == NULL)
		return (-1);
	va_start(ap, s);
	prt_byt = count_len(lst, ap);
	if (prt_byt != -1)
	{
		if (lst_print(lst) == -1)
			prt_byt = -1;
	}
	ft_lstclear(&lst, free);
	va_end(ap);
	return (prt_byt);
}
