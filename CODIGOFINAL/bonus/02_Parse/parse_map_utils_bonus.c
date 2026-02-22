/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 18:52:00 by thevaris          #+#    #+#             */
/*   Updated: 2026/02/22 18:52:00 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

static void	set_player(t_temp_map *map, int i, int start, int j)
{
	map->player->f_y = i;
	map->player->f_x = j;
	map->player->y = i - start;
	map->player->x = j;
	map->player->player = map->lines[map->player->y + start][map->player->x];
}

static int	set_j(char *line)
{
	int	j;

	j = 0;
	while (line[j] == ' ')
		j++;
	return (j);
}

static void	scan_map_line(t_temp_map *map, int i, int start, int *pcnt)
{
	int	j;

	j = set_j(map->lines[i]);
	if (start == 0 && (map->lines[i][j] == '1' || map->lines[i][j] == '0'
			|| map->lines[i][j] == DOOR_CHAR))
		return ;
	while (map->lines[i][++j] != '\0'
		&& check_line_player(start, map->lines[i][j], map) == 0)
		if (start != 0 && (player_check(map->lines[i][j], 0) == 1)
			&& (*pcnt)++ > -2)
			set_player(map, i, start, j);
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
		scan_map_line(map, i, start, &player_cnt);
	}
	if (player_cnt != 1)
		error_message(-12, map);
	map->start = ft_get_start_map(map);
	if (map->lines[map->start - 1][0] != '\0')
		error_message(-8, map);
	ft_do_flood(map, start, end, i);
}

char	*ft_remove_extra_spaces(char *str, t_temp_map *map)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	line = ft_calloc(sizeof(char), ft_strlen(str) + 1);
	if (!line)
		error_message(-15, map);
	while (is_whitespace(str[i]))
		i++;
	while (str[i])
	{
		while (str[i] && !is_whitespace(str[i]))
			line[j++] = str[i++];
		while (is_whitespace(str[i]))
			i++;
		if (i > 0 && str[i] != '\0')
			line[j++] = ' ';
	}
	line[j] = '\0';
	if (line[0] == 'C' || line[0] == 'F')
		line = ft_color_special(line, 0, 0, map);
	return (line);
}
