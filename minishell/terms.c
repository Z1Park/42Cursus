/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terms.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heejikim <heejikim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 15:32:48 by heejikim          #+#    #+#             */
/*   Updated: 2023/01/04 15:40:33 by heejikim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_terms(void)
{
	tcgetattr(STDIN_FILENO, &g_sys.old_term);
	tcgetattr(STDIN_FILENO, &g_sys.new_term);
	g_sys.new_term.c_lflag &= ~ECHOCTL;
	g_sys.new_term.c_cc[VQUIT] = 0;
}

void	apply_new_term(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_sys.new_term);
}

void	apply_old_term(void)
{
	tcsetattr(STDIN_FILENO, TCSANOW, &g_sys.old_term);
}
