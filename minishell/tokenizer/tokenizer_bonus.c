/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 15:27:55 by heejikim          #+#    #+#             */
/*   Updated: 2023/01/06 21:25:26 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "minishell_bonus.h"

void	append_arg(t_pipe *pipe, char *arg)
{
	int		i;
	char	**new_argv;

	new_argv = (char **)safe_malloc(sizeof(char *) * (pipe->argc + 2));
	i = 0;
	while (i < pipe->argc)
	{
		new_argv[i] = pipe->argv[i];
		i++;
	}
	new_argv[i] = arg;
	new_argv[i + 1] = NULL;
	safe_free(pipe->argv);
	pipe->argc++;
	pipe->argv = new_argv;
}

void	process_specials(t_token_list *list, const char **str, \
						void (*old_si)(int))
{
	if (**str == '<')
	{
		if (*(*str + 1) == '<')
			get_heredoc(list, str, old_si);
		else
			get_infile(list->tokens[list->size - 1], str);
	}
	else if (**str == '>')
	{
		if (*(*str + 1) == '>')
			get_outfile(list->tokens[list->size - 1], str, O_APPEND);
		else
			get_outfile(list->tokens[list->size - 1], str, O_TRUNC);
	}
	else if (**str == '(' || **str == ')')
		parse_parenthesis(list, str);
	else
		process_links(list, str);
}

void	process_word(t_token *token, const char **str)
{
	char	*word;
	char	**wildcard;
	int		wildcard_len;
	int		i;

	word = parse_word(str, 1);
	if (ft_strchr(word, '*'))
	{
		wildcard = find_wildcard_files(word);
		wildcard_len = get_split_size(wildcard);
		if (wildcard_len >= 1)
		{
			safe_free(word);
			i = -1;
			while (++i < wildcard_len)
				append_arg(token->cur_pipe, wildcard[i]);
			safe_free(wildcard);
		}
		else
			append_arg(token->cur_pipe, remove_backslash(word));
	}
	else
		append_arg(token->cur_pipe, word);
}

static void	check_redir_error(t_token *token)
{
	int		temp_fd[2];
	t_pipe	*pipe;

	pipe = token->pipes;
	while (pipe)
	{
		if (pipe->result == TOKEN_RD_FAIL)
		{
			temp_fd[0] = write_redirect("/tmp/errfd_in", O_TRUNC);
			if (pipe->redirect_in != READ)
			{
				close(pipe->redirect_in);
				pipe->redirect_in = temp_fd[0];
			}
		}
		if (pipe->result == TOKEN_WR_FAIL)
		{
			if (pipe->redirect_out != WRITE)
			{
				close(pipe->redirect_out);
				pipe->redirect_out = -1;
			}
		}
		pipe = pipe->next;
	}
}

t_token_list	*tokenize(const char *line, void (*old_si)(int))
{
	t_token_list	*list;
	int				i;

	list = (t_token_list *)safe_malloc(sizeof(t_token_list));
	init_token_list(list);
	append_token(list);
	create_pipe_info(list->tokens[0]);
	skip_space(&line);
	check_first_token(line, list);
	while (!list->interrupted && *line)
	{
		if (strchr("<>|&()", *line))
			process_specials(list, &line, old_si);
		else
			process_word(list->tokens[list->size - 1], &line);
		if (list->tokens[list->size - 1]->cur_pipe->result != TOKEN_SUCCESS)
			skip_pipe(&line);
		skip_space(&line);
	}
	i = -1;
	while (++i < list->size)
		check_redir_error(list->tokens[list->size - 1]);
	return (list);
}
