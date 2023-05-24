/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 09:36:31 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/06 15:00:13 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif
# ifndef OPEN_MAX
#  define OPEN_MAX 10240
# endif

typedef struct s_list
{
	char			*str;
	struct s_list	*next;
}	t_list;

char	*get_next_line(int fd);

size_t	ft_strlen(const char *s);
ssize_t	ft_strnchr(const char *s, char c, size_t len);
size_t	ft_strlcpy(char *s1, const char *s2, size_t n);
t_list	*make_strlst(void);
void	*free_lst(t_list *lst, char **s);

#endif
