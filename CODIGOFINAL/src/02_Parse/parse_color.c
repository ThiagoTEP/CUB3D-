/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:14:39 by thevaris          #+#    #+#             */
/*   Updated: 2026/01/04 20:14:40 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

int	check_colors_limits(char *line, t_temp_map *map)
{
	int		flag;
	char	**new;

	flag = 0;
	line[1] = ',';
	new = ft_split(line, ',');
	if (!new[0] || !new[1] || !new[2] || !new[3])
		return (free_split(new), error_message(-5, map));
	if (ft_atoi(new[1]) > 255 || ft_atoi(new[2]) > 255
		|| ft_atoi(new[3]) > 255)
		flag = -1;
	if (ft_atoi(new[1]) < 0 || ft_atoi(new[2]) < 0
		|| ft_atoi(new[3]) < 0)
		flag = -1;
	free_split(new);
	if (flag == -1)
		return (error_message(-6, map));
	return (1);
}

int	check_colors(char *line, t_temp_map *map, int comma, int i)
{
	while (line[i] != ' ' && line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i + 1] != '\0')
		i++;
	while (line[i] != '\0' && line[i] != '\n')
	{
		if (line[i] == ',' && i++ > 0)
			comma++;
		if (ft_isdigit(line[i]) == 0)
			return (-1);
		if (line[i] != '\n' && ft_isdigit(line[i]) == 0
			&& line[i] != ',' && !is_whitespace(line[i]))
			return (-1);
		if (line[i] != '\0' && line[i] != '\n')
			i++;
	}
	if ((line[i] != '\0' && line[i] != '\n') || comma != 2)
		return (error_message(-6, map));
	check_colors_limits(line, map);
	return (1);
}

bool	check_bools(bool val, t_temp_map *map)
{
	if (val == true)
		return (error_message(-11, map));
	return (true);
}

int	ft_invalid_start(t_temp_map *map, char c, int i)
{
	if (c == 'S' || c == 'N' || c == 'W' || c == 'E' || c == 'F'
		|| c == 'C' || c == '1' || c == '0' || c == '\0' || is_whitespace(c))
		check_next_char(map, c, i);
	else
		error_message(-7, map);
	if (c == 'S' || c == 'N' || c == 'W' || c == 'E'
		|| c == 'F' || c == 'C' || c == '1' || c == 0)
	{
		if (c == 'S' && map->lines[i][1] == 'O')
			map->valid->so = check_bools(map->valid->so, map);
		if (c == 'N' && map->lines[i][1] == 'O')
			map->valid->no = check_bools(map->valid->no, map);
		if (c == 'W' && map->lines[i][1] == 'E')
			map->valid->we = check_bools(map->valid->we, map);
		if (c == 'E' && map->lines[i][1] == 'A')
			map->valid->ea = check_bools(map->valid->ea, map);
		if (c == 'F' && map->lines[i][1] == ' ')
			map->valid->f = check_bools(map->valid->f, map);
		if (c == 'C' && map->lines[i][1] == ' ')
			map->valid->c = check_bools(map->valid->c, map);
	}
	return (1);
}

int	col_val(t_temp_map *map, int i)
{
	bool	color[2];

	color[0] = false;
	color[1] = false;
	while (map->lines[++i] != NULL && map->lines[i][0] != '1')
	{
		if (map->lines[i][0] == 'F' || map->lines[i][0] == 'C')
		{
			color[1 - (map->lines[i][0] - 67) / (70 - 67)] = true;
			if (check_colors(map->lines[i], map, 0, 0) == -1)
				return (error_message(-4, map));
		}
	}
	if (color[0] == false || color[1] == false)
		return (error_message(-5, map));
	return (1);
}
