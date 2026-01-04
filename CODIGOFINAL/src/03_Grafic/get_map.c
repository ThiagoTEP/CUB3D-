/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:15:08 by thevaris          #+#    #+#             */
/*   Updated: 2026/01/04 20:15:09 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

int	ft_get_max_line(int i, t_temp_map *map)
{
	int	max_len;

	max_len = -1;
	while (map->lines[i] != NULL)
	{
		if ((int)ft_strlen(map->lines[i]) > max_len)
			max_len = (int)ft_strlen(map->lines[i]);
		i++;
	}
	return (max_len + 1);
}

int	ft_get_colors(t_temp_map *map, int c)
{
	int		i;
	int		hex_color;
	char	**temp;

	i = 0;
	hex_color = 0;
	temp = NULL;
	while (map->lines[i] && map->lines[i][0] != c)
		i++;
	if (map->lines[i] && map->lines[i][0] == c)
	{
		map->lines[i][1] = ',';
		temp = ft_split(map->lines[i], ',');
		hex_color = rgb_to_int(ft_atoi(temp[1]),
				ft_atoi(temp[2]), ft_atoi(temp[3]));
		free_split(temp);
	}
	return (hex_color);
}

char	**get_final_map(t_temp_map *map)
{
	int		i;
	int		j;
	char	**new_map;
	int		max_line;

	i = 0;
	j = 0;
	new_map = NULL;
	first_check(map, 0);
	while (map->lines && map->lines[i][j] != '0'
			&& map->lines[i][j] != '1' && map->lines[i][j] != ' ')
		i++;
	new_map = ft_calloc(sizeof(char *), (map->size - i) + 1);
	max_line = ft_get_max_line(i, map);
	while (map->lines[i] != NULL && map->lines[i][0] != '\0'
		&& map->lines[i][0] != '\n')
	{
		new_map[j] = ft_copy_line(map->lines[i], max_line);
		i++;
		j++;
	}
	new_map[j] = NULL;
	return (new_map);
}

int	get_map_size(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
		i++;
	return (i);
}

char	*get_texture_path(t_temp_map *map, int c)
{
	int		i;
	char	**temp;
	char	*line;
	char	*path;

	path = NULL;
	line = NULL;
	i = 0;
	while (map->lines[i] && map->lines[i][0] != c)
		i++;
	if (map->lines[i][0] == c)
	{
		line = ft_remove_extra_spaces(map->lines[i], map);
		free(map->lines[i]);
		map->lines[i] = line;
		temp = ft_split(map->lines[i], ' ');
		if (temp[1] && !temp[2])
			path = ft_strdup(temp[1]);
		free_split(temp);
	}
	return (path);
}
