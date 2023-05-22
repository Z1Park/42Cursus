/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejikim <heejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 20:56:34 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/04 15:57:19 by heejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	check_validation(char *curr_env)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (curr_env[i] != '\0')
	{
		if (ft_isalnum(curr_env[i]) != 1 && curr_env[0] != '_')
		{
			tmp = ft_strjoin("unset: ", curr_env);
			print_error(ERR_INVALID_PARAM, tmp);
			safe_free(tmp);
			return (-1);
		}
		i++;
	}
	if (i == 0)
	{
		print_error(ERR_INVALID_PARAM, "unset: ");
		return (-1);
	}
	return (0);
}

static void	env_unset(size_t idx)
{
	size_t	size;
	char	**n_env;

	size = get_split_size(g_sys.p_env);
	n_env = copy_env(g_sys.p_env, size - 1, idx);
	while (idx < size - 1)
	{
		n_env[idx] = ft_strdup_uc(g_sys.p_env[idx + 1]);
		idx++;
	}
	n_env[idx] = NULL;
	free_splited(g_sys.p_env, size);
	g_sys.p_env = n_env;
}

static void	env_find_key(char *key)
{
	size_t	i;

	i = 0;
	while (g_sys.p_env[i] != NULL)
	{
		if (ft_strncmp(g_sys.p_env[i], key, ft_strlen(key)) == 0)
		{
			env_unset(i);
			return ;
		}
		i++;
	}
}

void	builtin_unset(t_pipe *token, int main_flag)
{
	int	i;
	int	err_flag;

	if (token->argc == 1)
		return ;
	err_flag = 0;
	i = 1;
	while (i < token->argc)
	{
		if (check_validation(token->argv[i]) == 0)
			env_find_key(token->argv[i]);
		else
			err_flag = 1;
		i++;
	}
	change_env_value("?", ft_itoa(err_flag));
	if (main_flag == 0)
		quit_shell(err_flag);
}
