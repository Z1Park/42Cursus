/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 16:43:28 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/05 13:44:56 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

size_t	get_split_size(char **arr)
{
	size_t	i;

	i = 0;
	while (arr[i] != NULL)
		i++;
	return (i);
}

void	free_splited(char **arr, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
		safe_free(arr[i++]);
	safe_free(arr);
}

int	hash(void *addr)
{
	unsigned long long	val;
	int					res;

	val = (unsigned long long)addr;
	res = 0;
	while (val)
	{
		res += val % 16;
		val /= 16;
	}
	return (res % HASH_MAX);
}

void	system_initialize(char **env)
{
	size_t	i;

	i = get_split_size(env);
	g_sys.p_env = copy_env(env, i + 1, i);
	g_sys.p_env[i] = ft_strdup_uc("?=0");
	g_sys.p_env[i + 1] = NULL;
	change_env_value("OLDPWD", "");
	print_logo();
}
