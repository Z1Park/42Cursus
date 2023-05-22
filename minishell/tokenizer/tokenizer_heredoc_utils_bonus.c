/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_heredoc_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 21:48:19 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/06 17:08:32 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

char	*heredoc_filename(void)
{
	static int	fileno;
	char		*filename_base;
	char		*fileno_str;
	char		*result;

	fileno++;
	filename_base = "/tmp/minishell_heredoc_";
	fileno_str = ft_itoa(fileno);
	result = ft_strjoin(filename_base, fileno_str);
	safe_free(fileno_str);
	return (result);
}

void	find_key_and_write(int fd, char *rd_buf, size_t len)
{
	char	*key;
	char	*tmp;

	key = ft_strndup(rd_buf, len);
	tmp = get_env_val(key);
	if (tmp == NULL)
		tmp = "";
	write(fd, tmp, ft_strlen(tmp));
	safe_free(key);
}

size_t	get_len_until_chr(char *str, char c)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && str[i] != c)
		i++;
	return (i);
}

size_t	get_delimitter_len(const char *str)
{
	size_t	i;
	size_t	len;
	char	quote;

	i = 0;
	len = 0;
	while (*str != '\0' && ft_strchr(" <>|&)", *str) == NULL)
	{
		if (*str == '\'' || *str == '\"')
		{
			quote = *(str++);
			while (*str != quote)
			{
				if (ft_strchr(" <>|&\0", *str) != NULL)
					return (0);
				len++;
				str++;
			}
			str++;
		}
		else
			len++;
		str++;
	}
	return (len);
}

char	*copy_delimitter(const char **str, size_t len, int *conv_flag)
{
	size_t	i;
	char	*result;
	char	quote;

	*conv_flag = 1;
	result = safe_malloc(sizeof(char) * (len + 2));
	i = 0;
	while (**str != '\0' && ft_strchr(" <>|&)", **str) == NULL)
	{
		if (**str == '\'' || **str == '\"')
		{
			*conv_flag = 0;
			quote = *(*str)++;
			while (**str != quote)
				result[i++] = *(*str)++;
			(*str)++;
		}
		else
			result[i++] = *(*str)++;
	}
	result[i++] = '\n';
	result[i] = '\0';
	return (result);
}
