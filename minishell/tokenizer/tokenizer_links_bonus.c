/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_links.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 22:26:07 by heejikim          #+#    #+#             */
/*   Updated: 2023/01/05 16:35:43 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	append_token(t_token_list *list)
{
	t_token	*new_token;
	t_token	**new_list;
	int		i;

	new_token = (t_token *)safe_malloc(sizeof(t_token));
	init_token(new_token);
	new_list = (t_token **)safe_malloc(sizeof(t_token *) * (list->size + 2));
	i = 0;
	while (i < list->size)
	{
		new_list[i] = list->tokens[i];
		i++;
	}
	new_list[list->size++] = new_token;
	new_list[list->size] = NULL;
	safe_free(list->tokens);
	list->tokens = new_list;
}

void	create_or_link(t_token_list *list)
{
	append_token(list);
	list->tokens[list->size - 1]->link_type = LINK_OR;
	create_pipe_info(list->tokens[list->size - 1]);
}

void	create_and_link(t_token_list *list)
{
	append_token(list);
	list->tokens[list->size - 1]->link_type = LINK_AND;
	create_pipe_info(list->tokens[list->size - 1]);
}

void	process_links(t_token_list *list, const char **str)
{
	if (**str == '|')
	{
		(*str)++;
		if (**str == '|')
		{
			(*str)++;
			create_or_link(list);
		}
		else
			create_pipe_info(list->tokens[list->size - 1]);
		change_env_value("?", "0");
	}
	else if (**str == '&')
	{
		(*str)++;
		if (**str == '&')
		{
			(*str)++;
			create_and_link(list);
			change_env_value("?", "0");
		}
	}
}
