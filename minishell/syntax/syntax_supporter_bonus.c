/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_supporter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:18:06 by heejikim          #+#    #+#             */
/*   Updated: 2023/01/06 12:06:34 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	check_quote(t_syntax *syntax, char **line)
{
	char	delimeter;

	if (syntax->last_char == ')')
		return (1);
	delimeter = **line;
	(*line)++;
	while (**line && **line != delimeter)
		(*line)++;
	if (**line != delimeter)
		return (1);
	syntax->last_char = **line;
	return (0);
}

int	check_link(t_syntax *syntax, char **line)
{
	if (ft_strchr("(<>|&", syntax->last_char))
		return (1);
	if (**line == '&' && *(*line + 1) != '&')
	{
		(*line)++;
		return (1);
	}
	if (**line == *(*line + 1))
		(*line)++;
	syntax->last_char = **line;
	return (0);
}

int	check_redirect(t_syntax *syntax, char **line)
{
	if (syntax->last_char == '<' || syntax->last_char == '>')
		return (1);
	if (**line == *(*line + 1))
		(*line)++;
	syntax->last_char = **line;
	return (0);
}

int	check_paren(t_syntax *syntax, char **line)
{
	if (**line == '(')
	{
		if (!ft_strchr("|&", syntax->last_char))
			return (1);
		while (*(*line + 1) == '(')
		{
			(*line)++;
			syntax->paren_depth++;
		}
		syntax->paren_depth++;
		syntax->last_char = **line;
		return (0);
	}
	if (syntax->last_char == '\0' || syntax->last_char == '('
		|| syntax->last_char == '<' || syntax->last_char == '>'
		|| syntax->last_char == '|' || syntax->last_char == '&')
		return (1);
	while (*(*line + 1) == ')')
	{
		(*line)++;
		syntax->paren_depth--;
	}
	syntax->paren_depth--;
	syntax->last_char = **line;
	return (0);
}

int	check_word(t_syntax *syntax, char *line)
{
	if (*line == ' ')
		return (0);
	if (syntax->last_char == ')')
		return (1);
	syntax->last_char = *line;
	return (0);
}
