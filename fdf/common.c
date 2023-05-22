/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 13:58:26 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/04 15:34:56 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	ft_swap(int *a, int *b)
{
	int	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

int	absolute(int a)
{
	if (a < 0)
		return (-a);
	else
		return (a);
}

int	get_max(int a, int b)
{
	if (a > b)
		return (a);
	else
		return (b);
}
