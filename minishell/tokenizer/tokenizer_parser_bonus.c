/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:23:15 by heejikim          #+#    #+#             */
/*   Updated: 2023/01/06 21:08:54 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	copy_env_val(char **dst, const char **src, char endl)
{
	char	*env_val;

	(*src)++;
	if (**src == endl)
	{
		*(*dst)++ = '$';
		return ;
	}
	if (**src == '?')
	{
		env_val = ft_strdup(get_env_val("?"));
		(*src)++;
	}
	else
	{
		env_val = get_env_val(*src);
		*src += get_keylen(*src);
	}
	if (!env_val)
		return ;
	while (*env_val)
	{
		**dst = *(env_val++);
		(*dst)++;
	}
}

void	copy_quote(char **dst, const char **src)
{
	char	delimeter;

	delimeter = **src;
	(*src)++;
	while (**src && **src != delimeter)
	{
		if (delimeter != '\'' && **src == '$')
		{
			copy_env_val(dst, src, delimeter);
			continue ;
		}
		if (**src == '*')
			*(*dst)++ = '\\';
		*(*dst)++ = *(*src)++;
	}
	(*src)++;
}

void	copy_word(char *dst, const char **src, int dollar_flag)
{
	while (!ft_strchr(" <>|&()", **src))
	{
		if (dollar_flag && **src == '$')
		{
			copy_env_val(&dst, src, '\0');
			continue ;
		}
		if (ft_strchr("'\"", **src))
		{
			copy_quote(&dst, src);
			continue ;
		}
		*dst++ = *(*src)++;
	}
	*dst = '\0';
}

char	*parse_word(const char **str, int dollar_flag)
{
	int		len;
	char	*res;

	len = token_word_len(*str, dollar_flag);
	res = (char *)safe_malloc(sizeof(char) * (len + 1));
	copy_word(res, str, dollar_flag);
	return (res);
}
