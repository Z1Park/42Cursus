/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 15:54:09 by heejikim          #+#    #+#             */
/*   Updated: 2023/01/05 19:24:41 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_space(const char **s)
{
	while (**s == ' ' || **s == '\n')
		(*s)++;
}

void	skip_quote(const char **s)
{
	char	delimeter;

	delimeter = **s;
	(*s)++;
	while (**s && **s != delimeter)
		(*s)++;
	if (**s == delimeter)
		(*s)++;
}

void	skip_pipe(const char **s)
{
	while (!ft_strchr("|&", **s))
	{
		if (ft_strchr("'\"", **s))
			skip_quote(s);
		(*s)++;
	}
}

size_t	write_until_dollor(char *rd_buf, int fd, int flag)
{
	size_t	i;

	i = get_len_until_chr(rd_buf + flag, '$') + flag;
	write(fd, rd_buf, i);
	return (i);
}
