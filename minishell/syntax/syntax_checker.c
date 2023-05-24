/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejikim <heejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 18:54:13 by heejikim          #+#    #+#             */
/*   Updated: 2023/01/05 21:47:12 by heejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_syntax	init_syntax(void)
{
	t_syntax	syntax;

	syntax.last_char = '\0';
	syntax.paren_depth = 0;
	return (syntax);
}

int	syntax_unclosed(t_syntax syntax)
{
	if ((syntax.last_char && ft_strchr("<>|&", syntax.last_char))
		|| syntax.paren_depth != 0)
		return (-1);
	return (0);
}

char	*check_syntax(char *line)
{
	t_syntax	syntax;
	int			err;

	syntax = init_syntax();
	err = 0;
	while (line && *line)
	{
		if (*line == '\'' || *line == '"')
			err = check_quote(&syntax, &line);
		else if (*line == '|' || *line == '&')
			err = check_link(&syntax, &line);
		else if (*line == '<' || *line == '>')
			err = check_redirect(&syntax, &line);
		else if (*line == '(' || *line == ')')
			err = check_paren(&syntax, &line);
		else
			err = check_word(&syntax, line);
		if (err || !*line || syntax.paren_depth < 0)
			return (line);
		line++;
	}
	if (syntax_unclosed(syntax))
		return (line);
	return (0);
}
