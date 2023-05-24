/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 20:56:34 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/06 17:17:27 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static size_t	check_validation(char *curr)
{
	char	*tmp;
	size_t	i;
	int		res;

	res = 1;
	if (ft_isalpha(curr[0]) != 1 && curr[0] != '_')
		res = 0;
	i = 0;
	while (res != 0 && curr[++i] != '\0' && curr[i] != '=')
	{
		if (ft_isalnum(curr[i]) != 1 && ft_strchr("_", curr[i]) == NULL)
			res = 0;
	}
	while (res != 0 && curr[++i] != '\0')
	{
		if (ft_isalnum(curr[i]) != 1 && ft_strchr("!`", curr[i]) != NULL)
			res = 0;
	}
	if (res == 0)
	{
		tmp = ft_strjoin("export: ", curr);
		print_error(ERR_INVALID_PARAM, tmp);
		safe_free(tmp);
	}
	return (res);
}

static int	find_match_key(char *find)
{
	size_t	i;
	size_t	key_len;
	char	*key;

	if (ft_strcmp(find, "_") == 0)
		return (1);
	if (ft_strchr(find, '=') == NULL)
		return (0);
	key_len = ft_strchr(find, '=') - find;
	key = ft_strndup(find, key_len);
	i = 0;
	while (g_sys.p_env[i] != NULL)
	{
		if (ft_strncmp(g_sys.p_env[i], key, key_len) == 0)
		{
			safe_free(g_sys.p_env[i]);
			g_sys.p_env[i] = ft_strdup_uc(find);
			safe_free(key);
			return (1);
		}
		i++;
	}
	safe_free(key);
	return (0);
}

static void	env_export(char *exp_str)
{
	size_t	size;
	char	**n_env;

	size = get_split_size(g_sys.p_env);
	n_env = copy_env(g_sys.p_env, size + 1, size - 2);
	n_env[size - 2] = ft_strdup_uc(exp_str);
	n_env[size - 1] = ft_strdup_uc(g_sys.p_env[size - 2]);
	n_env[size] = ft_strdup_uc(g_sys.p_env[size - 1]);
	n_env[size + 1] = NULL;
	free_splited(g_sys.p_env, size);
	g_sys.p_env = n_env;
}

static int	do_export(t_pipe *token)
{
	int	i;
	int	err_flag;

	err_flag = EXIT_NO_ERR;
	i = 0;
	while (++i < token->argc)
	{
		if (check_validation(token->argv[i]) != 0)
		{
			if (find_match_key(token->argv[i]) == 0)
				env_export(token->argv[i]);
		}
		else
			err_flag = EXIT_NORMAL_ERR;
	}
	return (err_flag);
}

void	builtin_export(t_pipe *token, int main_flag)
{
	int		err_flag;

	err_flag = EXIT_NO_ERR;
	if (token->argc == 1)
		builtin_env(token, "declare -x ");
	else
		err_flag = do_export(token);
	change_env_value("?", ft_itoa(err_flag));
	if (main_flag == 0)
		quit_shell(err_flag);
}
