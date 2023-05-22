/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_exit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejikim <heejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 10:26:10 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/04 16:06:23 by heejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_longlong_arrange(char *s, int sign)
{
	long long	res;

	res = 0;
	if (!*s)
		return (-1);
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (-1);
		if (sign == 1)
		{
			res = res * 10 + (*s - '0');
			if (res < 0)
				return (-1);
		}
		else
		{
			res = res * 10 - (*s - '0');
			if (res > 0)
				return (-1);
		}
		s++;
	}
	return (0);
}

static int	num_resize(int num)
{
	if (num > 255)
		num %= 256;
	else if (num < 0)
		num += 256 * (-1 * num / 256 + 1);
	return (num);
}

static int	exit_atoi(char *s)
{
	int	sign;
	int	num;

	num = 0;
	sign = 1;
	if (*s == '-' || *s == '+')
	{
		if (*s == '-')
			sign = -1;
		s++;
	}
	if (check_longlong_arrange(s, sign) < 0)
		return (-1);
	while (*s >= '0' && *s <= '9')
	{
		num = num * 10 + *s - '0';
		s++;
	}
	if (*s != '\0' && (*s < '0' || *s > '9'))
		return (-1);
	num *= sign;
	num = num_resize(num);
	return (num);
}

void	builtin_exit(t_pipe *token, int main_flag)
{
	int	exit_code;

	if (main_flag == 1)
		printf("exit\n");
	exit_code = 0;
	if (token->argv[1] != NULL)
		exit_code = exit_atoi(token->argv[1]);
	if (exit_code < 0)
	{
		print_error(ERR_NUM_ARG_REQ, ft_strjoin("exit: ", token->argv[1]));
		change_env_value("?", ft_itoa(EXIT_OUT_OF_RANGE));
		quit_shell(EXIT_OUT_OF_RANGE);
	}
	if (token->argc > 2)
	{
		print_error(ERR_TOO_MANY_ARGS, "exit");
		change_env_value("?", ft_itoa(EXIT_NORMAL_ERR));
		return ;
	}
	change_env_value("?", ft_itoa(exit_code));
	quit_shell(exit_code);
}
