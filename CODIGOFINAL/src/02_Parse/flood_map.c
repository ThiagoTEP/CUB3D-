/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:14:27 by thevaris          #+#    #+#             */
/*   Updated: 2026/01/04 20:14:28 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

int	check_the_sides(char **map, int y, int map_size)
{
	int	x;

	x = 0;
	while (y < map_size)
	{
		while (map[y][x] == ' ')
			x++;
		if (map[y][x] == 'F')
			return (-1);
		while (map[y][x] != '\0' && map[y][x] != '\n')
		{
			if (map[y][x] == 'F' && (!map[y + 1][x] || !map[y - 1][x]))
				return (-1);
			x++;
		}
		if (x > 0)
			x--;
		while (map[y][x] == ' ')
			x--;
		if (map[y][x] == 'F')
			return (-1);
		x = 0;
		y++;
	}
	return (1);
}

int	ft_check_first_last(char **map, int i)
{
	int	j;

	j = 0;
	while (map[i][j] != '\0')
	{
		if (map[i][j] == 'F')
			return (-1);
		j++;
	}
	while (map[i])
		i++;
	i--;
	j = 0;
	while (map[i][j] != '\0')
	{
		if (map[i][j] == 'F')
			return (-1);
		j++;
	}
	return (1);
}

void	flood(t_temp_map *map, int y, int x, int map_size)
{
	if (y > map_size || y < map->start)
		return ;
	if (x < 0 || x >= (int)ft_strlen(map->lines[y]))
		return ;
	if (map->lines[y][x] && map->lines[y][x] != '0' && map->lines[y][x] != ' '
		&& map->lines[y][x] != map->player->player)
		return ;
	if (map->lines[y][x] == '0' || map->lines[y][x] == ' ')
		map->lines[y][x] = 'F';
	if (map->lines[y][x] == 'N' || map->lines[y][x] == 'S'
		|| map->lines[y][x] == 'E' || map->lines[y][x] == 'W')
		map->lines[y][x] = 'F';
	flood(map, y + 1, x, map_size);
	flood(map, y - 1, x, map_size);
	flood(map, y, x + 1, map_size);
	flood(map, y, x - 1, map_size);
}

void	ft_do_flood(t_temp_map *map, int start, int end, int i)
{
	flood(map, map->player->f_y, map->player->f_x, i);
	if (ft_check_first_last(map->lines, start) == -1
		|| check_the_sides(map->lines, map->start + 1,
			end) == -1)
		error_message(-14, map);
}
