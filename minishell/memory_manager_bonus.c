/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/31 12:38:02 by heejikim          #+#    #+#             */
/*   Updated: 2022/12/31 18:29:50 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

void	*safe_malloc(size_t size)
{
	int		hash_val;
	t_mem	*node;

	node = malloc(sizeof(t_mem));
	if (!node)
		print_error(ERR_MALLOC, NULL);
	node->addr = malloc(size);
	if (!node->addr)
		print_error(ERR_MALLOC, NULL);
	node->collectible = COLLECTIBLE;
	hash_val = hash(node->addr);
	node->next = g_sys.alloc_mem[hash_val];
	g_sys.alloc_mem[hash_val] = node;
	return (node->addr);
}

void	*safe_malloc_uc(size_t size)
{
	int		hash_val;
	t_mem	*node;

	node = malloc(sizeof(t_mem));
	if (!node)
		print_error(ERR_MALLOC, NULL);
	node->addr = malloc(size);
	if (!node->addr)
		print_error(ERR_MALLOC, NULL);
	node->collectible = UNCOLLECTIBLE;
	hash_val = hash(node->addr);
	node->next = g_sys.alloc_mem[hash_val];
	g_sys.alloc_mem[hash_val] = node;
	return (node->addr);
}

void	safe_free(void *addr)
{
	int		hash_val;
	t_mem	*prev;
	t_mem	*cur;

	if (!addr)
		return ;
	hash_val = hash(addr);
	cur = g_sys.alloc_mem[hash_val];
	prev = NULL;
	while (cur)
	{
		if (cur->addr == addr)
		{
			if (!prev)
				g_sys.alloc_mem[hash_val] = cur->next;
			else
				prev->next = cur->next;
			free(cur->addr);
			free(cur);
			return ;
		}
		prev = cur;
		cur = cur->next;
	}
	free(addr);
}

void	collect_index(int i, int force_flag)
{
	t_mem	*prev;
	t_mem	*cur;
	t_mem	*next;

	cur = g_sys.alloc_mem[i];
	prev = NULL;
	while (cur)
	{
		next = cur->next;
		if (cur->collectible == COLLECTIBLE || force_flag)
		{
			if (!prev)
				g_sys.alloc_mem[i] = next;
			else
				prev->next = next;
			free(cur->addr);
			free(cur);
			cur = next;
			continue ;
		}
		prev = cur;
		cur = next;
	}
}

void	garbage_collect(int force_flag)
{
	int		i;

	i = 0;
	while (i < HASH_MAX)
	{
		collect_index(i, force_flag);
		i++;
	}
}
