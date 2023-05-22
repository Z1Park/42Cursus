/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 21:26:17 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/06 12:34:58 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static void	error_and_code(const char *s1, char *s2, int code, int flag)
{
	printf("minishell: %s: %s\n", s1, s2);
	change_env_value("?", ft_itoa(code));
	if (flag == TRUE)
	{
		garbage_collect(1);
		quit_shell(code);
	}
}

static void	syntax_error(const char *s)
{
	char	*temp;

	if (*s == '\0')
		temp = ft_strdup("newline");
	else if (*s == *(s + 1))
		temp = ft_strndup(s, 2);
	else
		temp = ft_strndup(s, 1);
	printf("minishell: syntax error near unexpected token `%s'\n", temp);
	safe_free(temp);
	change_env_value("?", "258");
}

static void	error_others(const char *s)
{
	perror(s);
	change_env_value("?", ft_itoa(EXIT_NORMAL_ERR));
	quit_shell(EXIT_NORMAL_ERR);
}

void	print_error(t_error err, const char *s)
{
	if (err == ERR_NOT_ENOUGH_ARGS)
		error_and_code(s, "not enough arguments", EXIT_NORMAL_ERR, TRUE);
	else if (err == ERR_TOO_MANY_ARGS)
		error_and_code(s, "too many arguments", EXIT_NORMAL_ERR, FALSE);
	else if (err == ERR_INVALID_PARAM)
		error_and_code(s, "not a valid identifier", EXIT_NORMAL_ERR, FALSE);
	else if (err == ERR_NUM_ARG_REQ)
		error_and_code(s, "numeric argument required", EXIT_OUT_OF_RANGE, TRUE);
	else if (err == ERR_NO_FILE)
		error_and_code(s, "No such file or directory", EXIT_NORMAL_ERR, FALSE);
	else if (err == ERR_AUTH_FAIL)
		error_and_code(s, "Permission denied", EXIT_NORMAL_ERR, FALSE);
	else if (err == ERR_NO_CMD)
		error_and_code(s, "command not found", EXIT_CMD_NOT_FOUND, FALSE);
	else if (err == ERR_AMBIGUOUS_REDIRECT)
		error_and_code(s, "ambiguous redirect", EXIT_NORMAL_ERR, FALSE);
	else if (err == ERR_NO_OLDPWD)
		error_and_code(s, "OLDPWD not set", EXIT_NORMAL_ERR, FALSE);
	else if (err == ERR_NO_HOME)
		error_and_code(s, "HOME not set", EXIT_NORMAL_ERR, FALSE);
	else if (err == ERR_SYNTAX)
		syntax_error(s);
	else
		error_others(s);
}

void	quit_shell(int code)
{
	apply_old_term();
	garbage_collect(1);
	exit(code);
}
