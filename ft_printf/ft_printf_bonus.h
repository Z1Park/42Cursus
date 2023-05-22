/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 02:37:03 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/16 20:26:30 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H
# include <stdlib.h>
# include "libft/libft.h"

typedef struct s_flag_info
{
	char	flags;
	size_t	width;
	size_t	prec;
}	t_flag_info;

enum	e_flag
{
	WIDTH		= 1 << 0,
	PRECISION	= 1 << 1,
	LEFT		= 1 << 2,
	ZERO_PAD	= 1 << 3,
	PREPEND		= 1 << 4,
	BLANK		= 1 << 5,
	SIGN		= 1 << 6,
};

int			ft_printf(const char *s, ...);

int			lst_add(t_list **lst, const char *s, int *len, t_ftype type);
t_list		*make_lst(const char *s, t_ftype type);
int			lst_print(t_list *lst);

int			get_max(int a, int b);
int			get_min(int a, int b);
size_t		get_pos(t_flag_info f_info, size_t buff, char *dst, size_t len);
void		right_align(t_flag_info f_info, size_t buff, char *dst, size_t len);
void		left_align(t_flag_info f_info, char *dst, size_t len);

t_flag_info	get_flags(char *str, int len);
t_ftype		get_ftype(char c);
int			get_buffer_size(t_flag_info f_info, t_ftype type, size_t s_len);

int			flag_to_char(t_list *lst, char c);
int			flag_to_str(t_list *lst, char *s);
int			flag_to_ptr(t_list *lst, void *s);
int			flag_to_int(t_list *lst, int d);
int			flag_to_uint(t_list *lst, unsigned int u);
int			flag_to_hex(t_list *lst, unsigned int x);
int			flag_to_pcnt(t_list *lst);

char		check_uint_zero(t_flag_info f_info, t_list *lst, \
	int buff, unsigned int d);

#endif
