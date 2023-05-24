/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_logo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/04 10:14:24 by jpark2            #+#    #+#             */
/*   Updated: 2023/01/04 10:53:48 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_h(int i)
{
	const char	*img[] = {"        __  __", "       / / / /", "      / /_/ /",
		"     / __  /", "    / / / /", "   /_/ /_/"};

	printf("\033[0;31m%s", img[i]);
}

static void	print_j(int i)
{
	const char	*img[] = {"_____", "__  /", "  / /",
		"  / /", "\\_/ /", "\\___/"};

	printf("\033[0;33m%s", img[i]);
}

static void	print_p(int i)
{
	const char	*img[] = {"____", " __ \\", " /_/ /", " ____/", " /", "_/"};

	printf("\033[0;34m%s", img[i]);
}

static void	print_sh(int i)
{
	const char	*img[] = {"       __    \n", "     / /    \n", "____/ /_    \n",
		" ___/ __ \\   \n", "  (___  ) / / /   \n", "  /_____/_/ /_/    \n"};

	printf("\033[0;0m%s", img[i]);
}

void	print_logo(void)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		print_h(i);
		print_j(i);
		print_p(i);
		print_sh(i);
		i++;
	}
	printf("                                    \n\n");
}
