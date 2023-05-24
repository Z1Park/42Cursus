/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_cd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 12:05:28 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/06 13:27:08 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_oldpwd(void)
{
	char	*oldpwd;

	oldpwd = get_env_val("OLDPWD");
	if (oldpwd == NULL || *oldpwd == '\0')
	{
		print_error(ERR_NO_OLDPWD, "cd");
		return (NULL);
	}
	printf("%s\n", oldpwd);
	return (oldpwd);
}

static char	*get_abs_path_from_home(char *path)
{
	char	*dir;
	char	*tmp;

	tmp = get_env_val("HOME");
	if (tmp == NULL)
	{
		print_error(ERR_NO_HOME, "cd");
		return (NULL);
	}
	if (path == NULL || (path[0] == '~' && path[1] == '\0'))
		dir = ft_strdup(tmp);
	else if (path != NULL)
		dir = ft_strjoin(tmp, path + 1);
	else
		dir = NULL;
	return (dir);
}

static char	*get_dir(t_pipe *token)
{
	char	*dir;
	char	*curr_pwd;

	if (token->argc == 1 || token->argv[1][0] == '~')
		dir = get_abs_path_from_home(token->argv[1]);
	else if (ft_strcmp(token->argv[1], "-") == 0)
		dir = get_oldpwd();
	else
		dir = token->argv[1];
	if (dir != NULL)
	{
		dir = ft_strdup(dir);
		curr_pwd = getcwd(NULL, BUF_MAX);
		change_env_value("OLDPWD", curr_pwd);
		free(curr_pwd);
	}
	return (dir);
}

static void	process_after_chdir(char *dir, int res)
{
	char	*tmp;
	char	*curr_pwd;

	if (res < 0)
	{
		tmp = ft_strjoin("cd: ", dir);
		print_error(ERR_NO_FILE, tmp);
		safe_free(tmp);
	}
	else
	{
		curr_pwd = getcwd(NULL, BUF_MAX);
		change_env_value("PWD", curr_pwd);
		free(curr_pwd);
	}
}

void	builtin_cd(t_pipe *token, int main_flag)
{
	char	*dir;
	int		res;

	dir = get_dir(token);
	if (dir == NULL)
		return ;
	res = chdir(dir);
	process_after_chdir(dir, res);
	safe_free(dir);
	if (main_flag == 0 && res == 0)
	{
		change_env_value("?", ft_itoa(EXIT_NO_ERR));
		quit_shell(EXIT_NO_ERR);
	}
}
