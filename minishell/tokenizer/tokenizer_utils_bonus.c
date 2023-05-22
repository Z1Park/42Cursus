/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejikim <heejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:19:18 by heejikim          #+#    #+#             */
/*   Updated: 2023/01/05 21:48:22 by heejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	init_token_list(t_token_list *list)
{
	list->interrupted = 0;
	list->size = 0;
	list->tokens = (t_token **)safe_malloc(sizeof(t_token *));
	list->tokens[0] = NULL;
}

void	init_token(t_token *token)
{
	token->link_type = LINK_NONE;
	token->pipes = NULL;
	token->cur_pipe = NULL;
	token->p_open = 0;
	token->p_close = 0;
}

void	create_pipe_info(t_token *token)
{
	t_pipe	*new_pipe;

	new_pipe = (t_pipe *)safe_malloc(sizeof(t_pipe));
	new_pipe->result = TOKEN_SUCCESS;
	new_pipe->argc = 0;
	new_pipe->argv = (char **)safe_malloc(sizeof(char *));
	new_pipe->argv[0] = 0;
	new_pipe->redirect_in = READ;
	new_pipe->redirect_out = WRITE;
	new_pipe->next = NULL;
	if (!token->pipes)
		token->pipes = new_pipe;
	if (token->cur_pipe)
		token->cur_pipe->next = new_pipe;
	token->cur_pipe = new_pipe;
}

char	*readline_with_nl(char *prompt)
{
	char	*temp;
	char	*result;

	temp = readline(prompt);
	if (!temp)
	{
		write(1, "\033[A> ", 5);
		free(temp);
		return (NULL);
	}
	result = ft_strjoin(temp, "\n");
	free(temp);
	return (result);
}

void	check_first_token(const char *line, t_token_list *list)
{
	char	*err_str;

	err_str = NULL;
	if (*line == '|')
	{
		if (*(line + 1) == '|')
			err_str = "||";
		else
			err_str = "|";
	}
	else if (*line == '&')
	{
		if (*(line + 1) == '&')
			err_str = "&&";
		else
			err_str = "&";
	}
	if (err_str != NULL)
	{
		list->interrupted = 1;
		print_error(ERR_SYNTAX, err_str);
	}
}
