/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 20:48:24 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/07 12:35:49 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*read_and_prompt(void)
{
	char	*line;
	char	*prompt;
	char	*err_pos;

	prompt = "heeJpark-shell$> ";
	g_sys.reading_flag = READING;
	line = readline(prompt);
	g_sys.reading_flag = IDLE;
	if (line == NULL)
	{
		printf("exit\n");
		quit_shell(0);
	}
	if (*line != '\0')
		add_history(line);
	err_pos = check_syntax(line);
	if (err_pos)
	{
		print_error(ERR_SYNTAX, err_pos);
		free(line);
		return (NULL);
	}
	return (line);
}

void	clear_tokens(t_token *tokens)
{
	t_pipe	*tmp;
	size_t	i;

	while (tokens->pipes != NULL)
	{
		tmp = tokens->pipes;
		tokens->pipes = tokens->pipes->next;
		i = 0;
		if (tmp->argc != 0)
		{
			while (tmp->argv[i] != NULL)
				safe_free(tmp->argv[i++]);
		}
		safe_free(tmp);
	}
	safe_free(tokens);
}

void	exec_line(t_token_list *list)
{
	int	i;

	i = 0;
	apply_old_term();
	token_parenthesis_recursive(list, i);
	apply_new_term();
}

int	main(int ac, __attribute__((unused)) char **av, char **env)
{
	char			*line;
	t_token_list	*tokens;
	void			(*old_sigint)(int);

	if (ac != 1)
		return (1);
	system_initialize(env);
	old_sigint = NULL;
	init_handlers(old_sigint);
	while (1)
	{
		line = read_and_prompt();
		if (line != NULL && *line != '\0')
		{
			tokens = tokenize(line, old_sigint);
			g_sys.reading_flag = IDLE;
			if (!tokens->interrupted)
				exec_line(tokens);
		}
		if (line != NULL)
			free(line);
		garbage_collect(0);
	}
	return (0);
}
