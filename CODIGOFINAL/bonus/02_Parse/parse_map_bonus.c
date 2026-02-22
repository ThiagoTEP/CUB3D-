/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:34:33 by thevaris          #+#    #+#             */
/*   Updated: 2026/02/22 18:52:00 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	first_check(t_temp_map *map, int i)
{
	while (map->lines[i] != NULL)
	{
		ft_invalid_start(map, map->lines[i][0], i);
		i++;
	}
}

int	check_line_player(int start, char c, t_temp_map *map)
{
	if (start != 0 && c != '\0' && c != '\n'
		&& c != 'N' && c != 'S'
		&& c != 'E' && c != 'W'
		&& c != '1' && c != '0'
		&& c != ' ' && c != DOOR_CHAR)
		error_message(-7, map);
	return (0);
}

int	player_check(char c, int flag)
{
	if (flag == 1 && (c != 'N' && c != 'S' && c != 'E' && c != 'W'))
		return (-1);
	if (flag == 0 && (c == 'N' || c == 'S' || c == 'E' || c == 'W'))
		return (1);
	return (0);
}

static int	check_empty_line(t_temp_map *map, int pos, int i)
{
	if (map->lines[pos][i] == '\0')
	{
		i = 0;
		while (map->lines[pos][i] == ' ')
			i++;
		if (map->lines[pos][i] == '\0')
			return (0);
		return (1);
	}
	return (-1);
}

int	ft_check_line(int pos, t_temp_map *map)
{
	int			i;
	static int	flag = 0;

	i = 0;
	while (map->lines[pos][i] != '\0' && (map->lines[pos][i] == '1'
		|| map->lines[pos][i] == '0' || map->lines[pos][i] == ' '
		|| map->lines[pos][i] == DOOR_CHAR))
		i++;
	if (map->lines[pos][i] != '\0' && map->lines[pos][i] != '1'
		&& map->lines[pos][i] != '0' && map->lines[pos][i] != ' '
		&& map->lines[pos][i] != DOOR_CHAR)
		if (player_check(map->lines[pos][i], 1) == -1)
			flag = 4;
	i = 0;
	while (map->lines[pos][i] != '\0' && map->lines[pos][i] != '1'
		&& map->lines[pos][i] != '0' && map->lines[pos][i] != DOOR_CHAR)
		i++;
	if (check_empty_line(map, pos, i) == 1)
		flag = 1;
	if (flag == 1 && (map->lines[pos][i] == '1' || map->lines[pos][i] == '0'
			|| map->lines[pos][i] == DOOR_CHAR))
		flag = 3;
	if (flag > 1)
		error_message(-13, map);
	return (0);
}
