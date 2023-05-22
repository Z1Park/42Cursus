/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pushswap.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 09:51:27 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/01 20:47:42 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSHSWAP_H
# define PUSHSWAP_H
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

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

long long	get_min(long long a, long long b);
long long	get_max(long long a, long long b);
long long	absolute(long long n);
size_t		find_min_node(t_dq_node *node);
size_t		find_max_node(t_dq_node *node);

void		dq_pushleft(t_deque *deque, long long value);
void		dq_pushright(t_deque *deque, long long value);
long long	dq_popleft(t_deque *deque);
long long	dq_popright(t_deque *deque);
t_deque		*create_deque(void);

void		swap(t_deque *deque, char dq);
void		push(t_deque *from, t_deque *to, char dq);
void		ss_swap(t_deque *deque1, t_deque *deque2);

void		rotate(t_deque *deque, char dq);
void		rev_rotate(t_deque *deque, char dq);
void		rr_rotate(t_deque *deque1, t_deque *deque2);
void		rrr_rotate(t_deque *deque1, t_deque *deque2);

size_t		ft_strlcpy(char *s1, const char *s2, size_t n);
long long	ft_atoi(const char *str);
char		**ft_split(char const *s, char c);

int			dq_is_sorted(t_deque *deque);
void		dq_clear(t_deque **deque);
t_dq_node	*find_node(t_deque *deque, size_t pos);
size_t		find_position(t_dq_node *node, t_dq_node *last, long long value);

void		sort_deque(t_deque *a_stk);
size_t		greedy_get_count(t_deque *a, t_deque *b, size_t b_pos);
void		greedy_move(t_deque *a, t_deque *b, size_t b_pos);

t_deque		*argument_parsing(int ac, char **av);

void		error_exit(void);

#endif
