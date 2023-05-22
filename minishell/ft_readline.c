/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejikim <heejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 16:49:11 by heejikim          #+#    #+#             */
/*   Updated: 2023/01/05 21:40:31 by heejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_realloc(char *str, int *size)
{
	char	*new_str;

	new_str = (char *)safe_malloc(sizeof(char) * (*size + 42));
	ft_strlcpy(new_str, str, *size + 1);
	*size += 42;
	safe_free(str);
	return (new_str);
}

char	*resize_line(char *str)
{
	char	*new_str;
	int		len;

	len = ft_strlen(str);
	if (len == 0)
	{
		safe_free(str);
		return (NULL);
	}
	new_str = (char *)safe_malloc(sizeof(char) * (len + 1));
	ft_strlcpy(new_str, str, len + 1);
	safe_free(str);
	return (new_str);
}

char	*ft_readline(void)
{
	char	*str;
	int		size;
	int		len;

	size = 42;
	str = (char *)safe_malloc(sizeof(char) * size);
	len = 0;
	str[0] = '\0';
	write(1, "> ", 2);
	while (1)
	{
		if (len >= size - 1)
			str = ft_realloc(str, &size);
		read(0, str + len, 1);
		str[++len] = '\0';
		if (str[len - 1] == '\n' || (len == 1 && str[len - 1] == '\0'))
			break ;
		if (str[len - 1] == '\0')
			len--;
	}
	return (resize_line(str));
}
