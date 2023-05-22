/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 10:22:19 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/31 18:39:59 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

char	**copy_env(char **env, size_t size, size_t idx)
{
	char	**n_env;
	size_t	i;

	n_env = safe_malloc_uc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < idx)
	{
		n_env[i] = ft_strdup_uc(env[i]);
		i++;
	}
	return (n_env);
}

int	ft_envcmp(const char *key, const char *env, int len)
{
	int	i;

	if (!ft_isalpha(*key) && ft_strcmp(key, "?") != 0)
		return (-1);
	i = 0;
	while (i < len)
	{
		if (*key++ != *env++)
			break ;
		i++;
	}
	if (i == len && *env == '=')
		return (0);
	return (-1);
}

int	get_keylen(const char *key)
{
	int	res;

	if (ft_strcmp(key, "?") == 0)
		return (1);
	res = 0;
	if (ft_isalpha(*key++))
		res++;
	else
		return (0);
	while (ft_isalnum(*key++))
		res++;
	return (res);
}

char	*get_env_val(const char *key)
{
	int	len;
	int	i;

	if (!ft_isalpha(*key) && ft_strcmp(key, "?") != 0)
		return (NULL);
	len = get_keylen(key);
	i = 0;
	while (g_sys.p_env[i])
	{
		if (!ft_envcmp(key, g_sys.p_env[i], len))
			return (g_sys.p_env[i] + len + 1);
		i++;
	}
	return (NULL);
}

int	change_env_value(char *key, char *value)
{
	int		len;
	int		i;
	char	*tmp;

	if (!ft_isalpha(*key) && ft_strcmp(key, "?") != 0)
		return (-1);
	len = get_keylen(key);
	i = 0;
	while (g_sys.p_env[i])
	{
		if (!ft_envcmp(key, g_sys.p_env[i], len))
		{
			tmp = ft_strjoin(key, "=");
			safe_free(g_sys.p_env[i]);
			g_sys.p_env[i] = ft_strjoin_uc(tmp, value);
			safe_free(tmp);
			return (0);
		}
		i++;
	}
	return (-1);
}
