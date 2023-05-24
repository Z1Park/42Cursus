/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 18:26:58 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/03 19:01:15 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "fdf.h"

void	print_error(t_error_no errno, char *s_err)
{
	if (errno == ERR_WRONG_INPUT)
		write(1, "Usage : ./fdf <filename> [ case_size z_size ]", 45);
	else if (errno == ERR_NO_FILE)
		write(1, "No file ", 8);
	else if (errno == ERR_NO_DATA)
		write(1, "No data found.", 14);
	else if (errno == ERR_WRONG_LENGTH)
		write(1, "Found wrong line length. Exiting.", 33);
	else if (errno == ERR_ALLOC_FAIL)
		perror(s_err);
	if (s_err != NULL)
		write(1, s_err, ft_strlen(s_err));
	write(1, "\n", 1);
	exit(EXIT_FAILURE);
}
