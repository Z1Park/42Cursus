/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_retouch_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 13:52:40 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/10 09:45:27 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	path_dir_check(char *filename)
{
	char	*tmp;
	char	*dir;

	tmp = ft_strrchr(filename, '/');
	if (tmp != NULL)
	{
		dir = malloc(sizeof(char) * (tmp - filename + 1));
		if (dir == NULL)
			print_error(ERR_MALLOC, NULL);
		ft_strlcpy(dir, filename, tmp - filename + 1);
		if (access(dir, F_OK) != 0)
			print_error(ERR_OPEN_FAIL, filename);
		free(dir);
	}
}

char	**here_doc_strs(char *s)
{
	char	**strs;
	size_t	len;

	strs = malloc(sizeof(char *) * 2);
	if (strs == NULL)
		print_error(ERR_MALLOC, NULL);
	len = ft_strlen(s);
	strs[0] = malloc(sizeof(char) * (len + 1));
	if (strs[0] == NULL)
		print_error(ERR_MALLOC, NULL);
	ft_strlcpy(strs[0], s, len + 1);
	strs[1] = NULL;
	return (strs);
}
