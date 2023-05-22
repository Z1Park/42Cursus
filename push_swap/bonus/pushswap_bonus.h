/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap_bonus.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 09:51:27 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/02 09:34:47 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_BONUS_H
# define PUSHSWAP_BONUS_H
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

# define BUFFER_SIZE 256
# ifndef OPEN_MAX
#  define OPEN_MAX 10240
# endif

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}	t_list;

typedef struct s_dq_node
{
	struct s_dq_node	*next;
	struct s_dq_node	*prev;
	long long			value;
}	t_dq_node;

typedef struct s_deque
{
	struct s_dq_node	*head;
	struct s_dq_node	*tail;
	size_t				dq_size;
}	t_deque;

void		dq_pushleft(t_deque *deque, long long value);
void		dq_pushright(t_deque *deque, long long value);
long long	dq_popleft(t_deque *deque);
long long	dq_popright(t_deque *deque);
t_deque		*create_deque(void);

void		swap(t_deque *deque);
void		push(t_deque *from, t_deque *to);
void		ss_swap(t_deque *deque1, t_deque *deque2);

void		rotate(t_deque *deque);
void		rev_rotate(t_deque *deque);
void		rr_rotate(t_deque *deque1, t_deque *deque2);
void		rrr_rotate(t_deque *deque1, t_deque *deque2);

size_t		ft_strlen(const char *s);
ssize_t		ft_strnchr(const char *s, char c, size_t len);
size_t		ft_strlcpy(char *s1, const char *s2, size_t n);
long long	ft_atoi(const char *str);
int			ft_strcmp(const char *s1, const char *s2);
char		**ft_split(char const *s, char c);

int			dq_is_sorted(t_deque *deque);
void		dq_clear(t_deque **deque);

t_deque		*argument_parsing(int ac, char **av);

void		error_exit(void);

#endif
