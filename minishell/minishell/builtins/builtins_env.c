/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 14:52:07 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/05 22:02:58 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sort_env(char **env, size_t	size)
{
	size_t	i;
	size_t	j;
	char	*temp;

	i = size - 3;
	while (i > 0)
	{
		j = 0;
		while (j < i)
		{
			if (ft_strcmp(env[j], env[j + 1]) > 0)
			{
				temp = env[j];
				env[j] = env[j + 1];
				env[j + 1] = temp;
			}
			j++;
		}
		i--;
	}
}

static void	print_env_with_prompt(char *prompt)
{
	char	**n_env;
	char	*tmp;
	char	*n_str;
	size_t	size;
	size_t	i;

	size = get_split_size(g_sys.p_env);
	n_env = copy_env(g_sys.p_env, size, size);
	sort_env(n_env, size);
	i = 0;
	while (i < size - 2)
	{
		tmp = ft_strchr(n_env[i], '=');
		if (tmp == NULL)
			printf("%s %s\n", prompt, n_env[i]);
		else
		{
			n_str = ft_strndup(n_env[i], tmp - n_env[i] + 1);
			printf("%s %s\"%s\"\n", prompt, n_str, tmp + 1);
			safe_free(n_str);
		}
		i++;
	}
	free_splited(n_env, size);
}

void	builtin_env(t_pipe *token, char *prompt)
{
	size_t	i;
	size_t	size;

	if (token->redirect_out != WRITE)
		dup2(token->redirect_out, STDOUT_FILENO);
	if (prompt == NULL)
	{
		i = 0;
		size = get_split_size(g_sys.p_env);
		while (i < size - 1 && ft_strrchr(g_sys.p_env[i], '=') != NULL)
			printf("%s\n", g_sys.p_env[i++]);
	}
	else
		print_env_with_prompt(prompt);
	change_env_value("?", ft_itoa(EXIT_NO_ERR));
	if (prompt == NULL)
		quit_shell(0);
}
