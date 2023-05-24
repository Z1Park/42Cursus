/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parenthesis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 19:25:37 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/04 21:21:54 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	parse_parenthesis(t_token_list *list, const char **str)
{
	if (**str == '(')
		list->tokens[list->size - 1]->p_open = 1;
	if (**str == ')')
		list->tokens[list->size - 1]->p_close = 1;
	(*str)++;
}

static int	skip_parenthesis_token(t_token_list *list, int i)
{
	while (i < list->size && list->tokens[i]->p_close == 0)
		i++;
	if (i < list->size)
		i++;
	return (i);
}

int	token_parenthesis_recursive(t_token_list *list, int i)
{
	int		status;

	while (i < list->size)
	{
		status = atoi(get_env_val("?"));
		if (list->tokens[i]->link_type == LINK_NONE
			|| (list->tokens[i]->link_type == LINK_AND && status == 0)
			|| (list->tokens[i]->link_type == LINK_OR && status != 0))
			do_commands(list->tokens[i]);
		if (i >= list->size - 1 || list->tokens[i]->p_close == 1)
			break ;
		status = atoi(get_env_val("?"));
		if (i < list->size - 1 && list->tokens[i + 1]->p_open == 1)
		{
			if ((list->tokens[i + 1]->link_type == LINK_AND && status == 0) \
				|| (list->tokens[i + 1]->link_type == LINK_OR && status != 0))
					i = token_parenthesis_recursive(list, ++i);
			else
				i = skip_parenthesis_token(list, ++i);
		}
		else
			i++;
	}
	return (++i);
}
