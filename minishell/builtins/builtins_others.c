/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_others.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 20:56:34 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/05 16:10:24 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_echo_newline_option(char *str)
{
	size_t	i;

	if (ft_strncmp(str, "-n", 2) != 0)
		return (-1);
	i = 2;
	while (str[i] != '\0' && str[i] == 'n')
		i++;
	if (str[i] != '\0')
		return (-1);
	return (0);
}

void	builtin_echo(t_pipe *token)
{
	int	i;

	if (token->redirect_out != WRITE)
		dup2(token->redirect_out, STDOUT_FILENO);
	if (token->argc == 1)
		printf("\n");
	else
	{
		i = 1;
		while (is_echo_newline_option(token->argv[i]) == 0)
			i++;
		while (i < token->argc)
		{
			printf("%s", token->argv[i]);
			if (i != token->argc - 1)
				printf(" ");
			i++;
		}
		if (is_echo_newline_option(token->argv[1]) != 0)
			printf("\n");
	}
	change_env_value("?", ft_itoa(EXIT_NO_ERR));
	quit_shell(EXIT_NO_ERR);
}

void	builtin_pwd(t_pipe *token)
{
	char	*path;

	path = getcwd(NULL, BUF_MAX);
	if (path == NULL)
		print_error(ERR_GET_CWD, NULL);
	if (token->redirect_out != WRITE)
		dup2(token->redirect_out, STDOUT_FILENO);
	printf("%s\n", path);
	safe_free(path);
	change_env_value("?", ft_itoa(EXIT_NO_ERR));
	quit_shell(EXIT_NO_ERR);
}
