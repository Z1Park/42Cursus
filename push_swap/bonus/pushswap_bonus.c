/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 21:22:06 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/02 09:54:40 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap_bonus.h"

void	error_exit(void)
{
	write(1, "Error\n", 6);
	exit(EXIT_FAILURE);
}

static void	do_cmd(char *cmd, t_deque *a, t_deque *b)
{
	if (ft_strcmp(cmd, "sa\n") == 0)
		swap(a);
	else if (ft_strcmp(cmd, "sb\n") == 0)
		swap(b);
	else if (ft_strcmp(cmd, "ss\n") == 0)
		ss_swap(a, b);
	else if (ft_strcmp(cmd, "pa\n") == 0)
		push(b, a);
	else if (ft_strcmp(cmd, "pb\n") == 0)
		push(a, b);
	else if (ft_strcmp(cmd, "ra\n") == 0)
		rotate(a);
	else if (ft_strcmp(cmd, "rb\n") == 0)
		rotate(b);
	else if (ft_strcmp(cmd, "rr\n") == 0)
		rr_rotate(a, b);
	else if (ft_strcmp(cmd, "rra\n") == 0)
		rev_rotate(a);
	else if (ft_strcmp(cmd, "rrb\n") == 0)
		rev_rotate(b);
	else if (ft_strcmp(cmd, "rrr\n") == 0)
		rrr_rotate(a, b);
	else
		error_exit();
}

static char	*ft_strjoin(char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*ret;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	ret = malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (ret == NULL)
		error_exit();
	ft_strlcpy(ret, s1, s1_len + 1);
	ft_strlcpy(&ret[s1_len], s2, s2_len + 1);
	free(s1);
	return (ret);
}

static char	*get_next_line(void)
{
	char	*buffer;
	char	*ret;
	ssize_t	rd;

	ret = NULL;
	buffer = malloc(sizeof(char) * 2);
	if (buffer == NULL)
		error_exit();
	rd = read(0, buffer, 1);
	while (rd > 0)
	{
		buffer[1] = 0;
		ret = ft_strjoin(ret, buffer);
		if (buffer[0] == '\n')
			break ;
		rd = read(0, buffer, 1);
	}
	if (rd == -1)
		error_exit();
	free(buffer);
	return (ret);
}

int	main(int ac, char **av)
{
	t_deque		*a_stk;
	t_deque		*b_stk;
	char		*read_cmd;

	a_stk = argument_parsing(ac, av);
	b_stk = create_deque();
	read_cmd = get_next_line();
	while (read_cmd > 0)
	{
		do_cmd(read_cmd, a_stk, b_stk);
		free(read_cmd);
		read_cmd = get_next_line();
	}
	if (b_stk->dq_size == 0 && dq_is_sorted(a_stk) == 0)
		write(1, "OK\n", 3);
	else
		write(1, "KO\n", 3);
	dq_clear(&a_stk);
	dq_clear(&b_stk);
	return (0);
}
