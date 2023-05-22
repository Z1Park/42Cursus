/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_control_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 14:10:34 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/10 12:45:26 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	ft_put_str(const char *s)
{
	if (s != NULL && *s != 0)
		write(1, s, ft_strlen(s));
}

static void	put_error(char *error, char *s)
{
	ft_put_str("pipex: ");
	ft_put_str(error);
	ft_put_str(": ");
	ft_put_str(s);
	ft_put_str("\n");
}

void	print_error(t_error err, char *s)
{
	if (err == ERR_OPEN_FAIL)
		put_error("no such file or directory", s);
	else if (err == ERR_NO_CMD)
		put_error("command not found", s);
	else if (err == ERR_PERM_DENY)
		put_error("permission denied", s);
	else
	{
		if (err == ERR_CHILD_FAIL)
			strerror(ECHILD);
		else if (err == ERR_PIPE)
			strerror(EPIPE);
		else if (err == ERR_FORK)
			strerror(EAGAIN);
		else if (err == ERR_PARAM)
			ft_put_str("pipex: arguments should be more than 3\n");
		exit(EXIT_FAILURE);
	}
}
