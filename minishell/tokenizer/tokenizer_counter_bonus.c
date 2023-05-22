/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_counter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:22:37 by heejikim          #+#    #+#             */
/*   Updated: 2023/01/06 21:08:23 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	env_len(const char **str, char endl)
{
	char	*env_val;

	(*str)++;
	if (**str == endl)
		return (1);
	if (**str == '?')
	{
		env_val = get_env_val("?");
		(*str)++;
	}
	else
	{
		env_val = get_env_val(*str);
		*str += get_keylen(*str);
	}
	if (!env_val)
		return (0);
	return (ft_strlen(env_val));
}

int	quote_len(const char **str)
{
	char	delimeter;
	int		len;

	delimeter = **str;
	len = 0;
	(*str)++;
	while (**str && **str != delimeter)
	{
		if (delimeter != '\'' && **str == '$')
		{
			len += env_len(str, delimeter);
			continue ;
		}
		if (**str == '*')
			len++;
		(*str)++;
		len++;
	}
	return (len);
}

int	token_word_len(const char *str, int dollar_flag)
{
	int	len;

	len = 0;
	while (!ft_strchr(" \n<>|&()", *str))
	{
		if (dollar_flag && *str == '$')
		{
			len += env_len(&str, '\0');
			continue ;
		}
		if (ft_strchr("'\"", *str))
		{
			len += quote_len(&str);
			continue ;
		}
		len++;
		str++;
	}
	return (len);
}
