/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/11 18:53:05 by jpark2            #+#    #+#             */
/*   Updated: 2023/03/08 15:58:17 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"

void	argv_free(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
		free(argv[i++]);
	free(argv);
}

int	get_argv_size(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != NULL)
		i++;
	return (i);
}

double	light_attenuation(double brightness, double distance)
{
	return (1000000 * brightness / distance / distance);
}

t_vec	string_to_vec(char *s)
{
	char	**strs;
	t_vec	v;

	strs = ft_split(s, ',');
	if (get_argv_size(strs) != 3)
		error_exit("Error\aObject rgument error\n");
	v = vec(ft_atod(strs[0]), ft_atod(strs[1]), ft_atod(strs[2]));
	argv_free(strs);
	return (v);
}

double	clamp(double x, double min, double max)
{
	if (x < min)
		return (min);
	if (x > max)
		return (max);
	return (x);
}
