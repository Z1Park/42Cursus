/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 02:37:03 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/16 16:57:44 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdlib.h>
# include "libft/libft.h"

int			ft_printf(const char *s, ...);

int			lst_add(t_list **lst, const char *s, int *len, t_ftype type);
t_list		*make_lst(const char *s, t_ftype type);
int			lst_print(t_list *lst);

t_ftype		get_ftype(char c);
size_t		get_hex_len(unsigned long long x);

int			flag_to_char(t_list *lst, char c);
int			flag_to_str(t_list *lst, char *s);
int			flag_to_ptr(t_list *lst, void *s);
int			flag_to_int(t_list *lst, int d);
int			flag_to_uint(t_list *lst, unsigned int u);
int			flag_to_hex(t_list *lst, unsigned int x);
int			flag_to_pcnt(t_list *lst);

#endif
