/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 15:10:38 by jpark2            #+#    #+#             */
/*   Updated: 2023/02/11 15:20:17 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "libft.h"
# include <unistd.h>

# define BUFFER_SIZE 1024

char	*get_next_line(int fd);
t_list	*make_strlst(void);
void	*free_lst(t_list *lst, char **s);
ssize_t	ft_strnchr(const char *s, char c, size_t len);

#endif
