/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 16:50:09 by heejikim          #+#    #+#             */
/*   Updated: 2023/01/07 12:35:29 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(__attribute__((unused))int sig)
{
	if (g_sys.reading_flag == READING)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	else if (g_sys.reading_flag != HEREDOC)
		write(1, "\n", 1);
	change_env_value("?", ft_itoa(EXIT_NORMAL_ERR));
}

void	sigquit_handler(__attribute__((unused)) int sig)
{
	if (g_sys.reading_flag == READING)
	{
		rl_on_new_line();
		rl_redisplay();
	}
	else
		printf("Quit: 3\n");
}

void	init_handlers(void (*old_sigint)(int))
{
	init_terms();
	apply_new_term();
	old_sigint = signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
