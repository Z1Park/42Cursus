/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 15:52:49 by jpark2            #+#    #+#             */
/*   Updated: 2022/11/04 15:52:49 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pushswap.h"

static int	count_args(int ac, char **av)
{
	int	i;
	int	j;
	int	count;

	i = 1;
	count = 0;
	while (i < ac)
	{
		j = 0;
		while (av[i][j] != 0)
		{
			while (av[i][j] == ' ')
				j++;
			if (av[i][j] == '+' || av[i][j] == '-')
				j++;
			if (av[i][j] != 0 && (av[i][j] < '0' || av[i][j] > '9'))
				error_exit();
			if (av[i][j] >= '0' && av[i][j] <= '9')
				count++;
			while (av[i][j] >= '0' && av[i][j] <= '9')
				j++;
		}
		i++;
	}
	return (count);
}

static long long	*arg_to_int(int ac, char **av, int count)
{
	long long	*nums;
	char		**tmp;
	int			i;
	int			j;
	int			k;

	nums = malloc(sizeof(long long) * (count));
	if (nums == NULL)
		error_exit();
	i = 0;
	j = 0;
	while (++j < ac)
	{
		k = 0;
		tmp = ft_split(av[j], ' ');
		while (tmp[k] != NULL)
		{
			nums[i++] = ft_atoi(tmp[k]);
			if (nums[i - 1] > 2147483647 || nums[i - 1] < -2147483648)
				error_exit();
			free(tmp[k++]);
		}
		free(tmp);
	}
	return (nums);
}

static void	check_sort_dup(long long *nums, int count)
{
	int	i;
	int	j;

	i = 0;
	while (i < (int)count)
	{
		j = i + 1;
		while (j < count)
		{
			if (nums[i] == nums[j])
				error_exit();
			j++;
		}
		i++;
	}
	i = 0;
	while (i < count - 1)
	{
		if (nums[i] > nums[i + 1])
			return ;
		i++;
	}
	exit(EXIT_SUCCESS);
}

static void	num_to_rank(long long *nums, int count)
{
	long long		min;
	int				i;
	int				rank;

	rank = 1;
	while (rank < count + 1)
	{
		min = 2147483648;
		i = 0;
		while (i < count)
		{
			if (nums[i] < min && (rank == 1 || nums[i] >= rank))
				min = nums[i];
			i++;
		}
		i = 0;
		while (i < count)
		{
			if (rank == 1 || nums[i] > rank)
				nums[i] += rank - min;
			i++;
		}
		rank++;
	}
}

t_deque	*argument_parsing(int ac, char **av)
{
	int				i;
	int				count;
	long long		*nums;
	t_deque			*deque;

	deque = NULL;
	if (ac == 1)
		exit(EXIT_SUCCESS);
	else
	{
		count = count_args(ac, av);
		nums = arg_to_int(ac, av, count);
		if (count == 1)
			exit(EXIT_SUCCESS);
		check_sort_dup(nums, count);
		num_to_rank(nums, count);
		deque = create_deque();
		i = 0;
		while (i < count)
			dq_pushright(deque, nums[i++]);
		free(nums);
	}
	return (deque);
}
