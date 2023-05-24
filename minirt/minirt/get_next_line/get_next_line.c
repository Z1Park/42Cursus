/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 09:36:12 by jpark2            #+#    #+#             */
/*   Updated: 2023/02/11 15:29:20 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*seperate_nl(char **remain, char *s, ssize_t nl_idx, size_t s_len)
{
	char	*ret;
	char	*tmp;

	ret = malloc(sizeof(char) * (nl_idx + 1));
	if (ret == NULL)
		return (free_lst(NULL, remain));
	ft_strlcpy(ret, s, nl_idx + 1);
	tmp = NULL;
	if (s_len > (size_t)nl_idx)
	{
		tmp = malloc(sizeof(char) * (s_len - nl_idx + 1));
		if (tmp == NULL)
		{
			free(ret);
			ret = NULL;
		}
		else
			ft_strlcpy(tmp, &(s[nl_idx]), s_len - nl_idx + 1);
	}
	free(*remain);
	*remain = tmp;
	return (ret);
}

static ssize_t	read_until_nl(t_list *lst, int fd)
{
	ssize_t	rd;

	if (lst == NULL || lst->content == NULL)
		return (-1);
	rd = read(fd, lst->content, BUFFER_SIZE);
	while (rd > 0 && rd == BUFFER_SIZE)
	{
		if (ft_strnchr(lst->content, '\n', BUFFER_SIZE) != -1)
			break ;
		lst->next = make_strlst();
		if (lst->next == NULL)
			return (-1);
		lst = lst->next;
		rd = read(fd, lst->content, BUFFER_SIZE);
	}
	return (rd);
}

static char	*get_strlst_malloc(t_list *lst, size_t len, ssize_t last_rd)
{
	size_t	total_len;
	ssize_t	idx;
	char	*ret;

	total_len = 0;
	while (lst->next != NULL)
	{
		total_len += BUFFER_SIZE;
		lst = lst->next;
	}
	idx = ft_strnchr(lst->content, '\n', last_rd);
	if (idx == -1)
		total_len += last_rd;
	else
		total_len += idx;
	if (len == 0 && total_len == 0)
		return (NULL);
	ret = malloc(sizeof(char) * (len + total_len + 1));
	return (ret);
}

static char	*str_concat(char **rm, size_t len, t_list *lst, ssize_t last_rd)
{
	char	*ret;
	char	*tmp;
	ssize_t	nl_idx;
	t_list	*first;

	ret = get_strlst_malloc(lst, len, last_rd);
	if (ret == NULL)
		return (free_lst(lst, NULL));
	if (*rm != NULL)
		ft_strlcpy(ret, *rm, len + 1);
	first = lst;
	while (lst->next != NULL)
	{
		len += ft_strlcpy(&ret[len], lst->content, BUFFER_SIZE + 1);
		lst = lst->next;
	}
	nl_idx = ft_strnchr(lst->content, '\n', last_rd);
	if (nl_idx == -1)
		nl_idx = last_rd;
	tmp = seperate_nl(rm, lst->content, nl_idx, last_rd);
	if (tmp == NULL)
		return (free_lst(first, &ret));
	ft_strlcpy(&ret[len], tmp, nl_idx + 1);
	free_lst(first, &tmp);
	return (ret);
}

char	*get_next_line(int fd)
{
	static char	*rms;
	ssize_t		idx;
	size_t		r_len;
	t_list		*strlst;
	char		*ret;

	r_len = 0;
	if (rms != NULL)
	{
		r_len = ft_strlen(rms);
		idx = ft_strnchr(rms, '\n', r_len);
		if (idx != -1)
			return (seperate_nl(&rms, rms, idx, r_len));
	}
	strlst = make_strlst();
	idx = read_until_nl(strlst, fd);
	if (idx == -1)
		return (free_lst(strlst, &rms));
	ret = str_concat(&rms, r_len, strlst, idx);
	if (ret == NULL)
		free_lst(NULL, &rms);
	return (ret);
}
