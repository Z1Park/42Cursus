/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_infile.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejikim <heejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/26 10:58:02 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/04 18:53:17 by heejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	read_redirect(char *filename)
{
	int	fd;

	if (!filename)
		return (-1);
	if (access(filename, F_OK) == -1)
	{
		print_error(ERR_NO_FILE, filename);
		return (-1);
	}
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		print_error(ERR_AUTH_FAIL, filename);
		return (-1);
	}
	return (fd);
}

char	*parse_filename(t_token *token, const char **str)
{
	char	*res;
	char	**wildcard;

	res = parse_word(str, 1);
	if (!ft_strchr(res, '*'))
		return (res);
	wildcard = find_wildcard_files(res);
	if (get_split_size(wildcard) > 1)
	{
		print_error(ERR_AMBIGUOUS_REDIRECT, res);
		token->cur_pipe->result = TOKEN_RD_FAIL;
		safe_free(res);
		free_splited(wildcard, get_split_size(wildcard));
		return (NULL);
	}
	if (get_split_size(wildcard) == 1)
	{
		safe_free(res);
		res = wildcard[0];
	}
	safe_free(wildcard);
	return (res);
}

void	get_infile(t_token *token, const char **str)
{
	char	*filename;

	(*str)++;
	skip_space(str);
	filename = parse_filename(token, str);
	if (token->cur_pipe->redirect_in != 0)
	{
		close(token->cur_pipe->redirect_in);
		token->cur_pipe->redirect_in = 0;
	}
	token->cur_pipe->redirect_in = read_redirect(filename);
	if (token->cur_pipe->redirect_in < 0)
	{
		token->cur_pipe->result = TOKEN_RD_FAIL;
		token->cur_pipe->redirect_in = -1;
	}
	safe_free(filename);
}
