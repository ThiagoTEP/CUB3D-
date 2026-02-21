/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:34:33 by thevaris          #+#    #+#             */
/*   Updated: 2026/02/20 16:34:34 by thevaris         ###   ########.fr       */
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
	if (map->lines[pos][i] == '\0')
	{
		i = 0;
		while (map->lines[pos][i] == ' ')
			i++;
		if (map->lines[pos][i] == '\0')
			return (0);
		flag = 1;
	}
	if (flag == 1 && (map->lines[pos][i] == '1' || map->lines[pos][i] == '0'
			|| map->lines[pos][i] == DOOR_CHAR))
		flag = 3;
	if (flag > 1)
		error_message(-13, map);
	return (0);
}

void	set_player(t_temp_map *map, int i, int start, int j)
{
	map->player->f_y = i;
	map->player->f_x = j;
	map->player->y = i - start;
	map->player->x = j;
	map->player->player = map->lines[map->player->y + start][map->player->x];
}

int	set_j(char *line)
{
	int	j;

	j = 0;
	while (line[j] == ' ')
		j++;
	return (j);
}

void	check_map(t_temp_map *map, int start, int end, int i)
{
	int	j;
	int	player_cnt;

	player_cnt = 0;
	while (map->lines[++i])
	{
		j = set_j(map->lines[i]);
		if (start == 0 && (map->lines[i][j] == '1' || map->lines[i][j] == '0'
				|| map->lines[i][j] == DOOR_CHAR))
			start = i;
		else if (map->lines[i][j] == '1' || map->lines[i][j] == '0'
			|| map->lines[i][j] == DOOR_CHAR)
			end = i;
		if (start != 0)
			ft_check_line(i, map);
		while (map->lines[i][++j] != '\0'
			&& check_line_player(start, map->lines[i][j], map) == 0)
			if (start != 0 && (player_check(map->lines[i][j], 0) == 1)
				&& player_cnt++ > -2)
				set_player(map, i, start, j);
	}
	if (player_cnt != 1)
		error_message(-12, map);
	map->start = ft_get_start_map(map);
	if (map->lines[map->start - 1][0] != '\0')
		error_message(-8, map);
	ft_do_flood(map, start, end, i);
}
