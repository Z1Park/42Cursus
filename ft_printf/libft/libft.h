/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 13:01:31 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/14 16:34:57 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <stdlib.h>

typedef enum e_ftype
{
	T_NONE,
	T_CHAR,
	T_PTR,
	T_STR,
	T_INT,
	T_UINT,
	T_LHEX,
	T_UHEX,
	T_PCNT,
}	t_ftype;

typedef struct s_list
{
	struct s_list	*next;
	t_ftype			type;
	int				s_len;
	char			*str;
}	t_list;

size_t	ft_strlen(const char *s);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
int		ft_atoi(const char *str);
void	*ft_memset(void *b, int c, size_t n);
void	*ft_calloc(size_t count, size_t size);
char	*ft_strdup(const char *s1, size_t len);
char	*ft_itoa(int n, char flag, size_t prec);
char	*ft_uitoa(unsigned int n, size_t prec);

t_list	*ft_lstnew(void *content, int len, t_ftype type);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstclear(t_list **lst, void (*del)(void *));

#endif
