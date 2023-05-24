/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpark2 <jpark2@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/03 14:43:23 by jpark2            #+#    #+#             */
/*   Updated: 2022/12/06 13:59:47 by jpark2           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "fdf.h"

static t_map	*get_map_size(int fd)
{
	char	*line;
	size_t	words;
	t_map	*map;

	map = malloc(sizeof(t_map));
	if (map == NULL)
		print_error(ERR_ALLOC_FAIL, NULL);
	map->width = 0;
	map->height = 0;
	map->gap_pixel = PIXEL_GAP;
	line = get_next_line(fd);
	while (line != NULL)
	{
		words = count_words(line, ' ');
		if (map->width == 0)
			map->width = words;
		else if (map->width != (int)words)
			print_error(ERR_WRONG_LENGTH, NULL);
		map->height += 1;
		free(line);
		line = get_next_line(fd);
	}
	return (map);
}

static void	map_allocation(t_map *map)
{
	int	i;

	map->data = malloc(sizeof(long long *) * map->height);
	if (map->data == NULL)
		print_error(ERR_ALLOC_FAIL, NULL);
	map->color = malloc(sizeof(long long *) * map->height);
	if (map->color == NULL)
		print_error(ERR_ALLOC_FAIL, NULL);
	i = 0;
	while (i < map->height)
	{
		map->data[i] = malloc(sizeof(long long) * map->width);
		if (map->data[i] == NULL)
			print_error(ERR_ALLOC_FAIL, NULL);
		map->color[i] = malloc(sizeof(int) * map->width);
		if (map->color[i] == NULL)
			print_error(ERR_ALLOC_FAIL, NULL);
		i++;
	}
}

static int	check_color(char *s)
{
	size_t	i;
	int		color;

	while (*s >= '0' && *s <= '9')
		s++;
	if (*(s++) != ',')
		return (0x00FFFFFF);
	color = hex_to_int(s);
	return (color);
}

static void	str_to_map(t_map *map, int fd)
{
	char	*line;
	char	**tmp;
	int		i;
	int		j;

	line = get_next_line(fd);
	i = 0;
	while (i < map->height && line != NULL)
	{
		tmp = ft_split(line, ' ');
		j = 0;
		while (tmp[j] != NULL)
		{
			map->data[i][j] = ft_atoi(tmp[j]);
			map->color[i][j] = check_color(tmp[j]);
			free(tmp[j++]);
		}
		free(tmp);
		free(line);
		line = get_next_line(fd);
		i++;
	}
}

t_map	*file_parsing(char *file_name)
{
	int		fd;
	t_map	*map;

	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		print_error(ERR_NO_FILE, file_name);
	map = get_map_size(fd);
	close(fd);
	if (map->width == 0 || map->height == 0)
		print_error(ERR_NO_DATA, NULL);
	map_allocation(map);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		print_error(ERR_NO_FILE, file_name);
	str_to_map(map, fd);
	close(fd);
	return (map);
}
