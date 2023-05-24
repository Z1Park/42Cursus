/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 09:36:31 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/09 16:28:44 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_BONUS_H
# define GNL_BONUS_H
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"

# define BUFFER_SIZE 1024
# ifndef OPEN_MAX
#  define OPEN_MAX 10240
# endif

char	*get_next_line(int fd);

size_t	ft_strlen(const char *s);
ssize_t	ft_strnchr(const char *s, char c, size_t len);
size_t	ft_strlcpy(char *s1, const char *s2, size_t n);
t_list	*make_strlst(void);
void	*free_lst(t_list *lst, char **s);

#endif
