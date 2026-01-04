/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:14:04 by thevaris          #+#    #+#             */
/*   Updated: 2026/01/04 20:14:05 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

int	ft_get_file_size(char *file, t_temp_map *map)
{
	int		fd;
	int		size;
	char	*line;

	size = 0;
	fd = open(file, O_RDONLY);
	if (fd < -1)
		return (EXIT_FAILURE);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (size > 50 || ft_strlen(line) > 150)
			ft_end_gnl(fd, map, line);
		size++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (size + 1);
}

char	*swap_strings(char *str, t_temp_map *map)
{
	char	*new_str;

	if (str[0] == '\0')
		return (str);
	new_str = ft_remove_extra_spaces(str, map);
	free(str);
	return (new_str);
}

int	ft_check_start(t_temp_map *map, char *line)
{
	char	*temp;

	temp = ft_remove_extra_spaces(line, map);
	if (temp[0] == '\0' || (temp[0] != '1'
			&& temp[0] != '0' && temp[0] != '\n'))
		return (free(temp), -1);
	free(temp);
	return (1);
}

void	ft_get_map(t_temp_map **map, char *file, int i, int j)
{
	int	fd;
	int	not_map;

	not_map = -1;
	(*map)->lines = ft_calloc(sizeof(char *), (*map)->size + 1);
	(*map)->valid = ft_calloc(sizeof(t_valid_map), 1);
	fd = open (file, O_RDONLY);
	if (fd < 0)
		error_message(-1, (*map));
	(*map)->lines[i] = get_next_line(fd);
	while ((*map)->lines[i] != NULL)
	{
		while ((*map)->lines[i][j] != '\0' && (*map)->lines[i][j] != '\n')
			j++;
		(*map)->lines[i][j] = '\0';
		if (not_map == -1 && ft_check_start(*map, (*map)->lines[i]) == 1)
			not_map = 1;
		if (not_map == -1)
			(*map)->lines[i] = swap_strings((*map)->lines[i], *map);
		j = 0;
		(*map)->lines[++i] = get_next_line(fd);
	}
	(*map)->lines[i + 1] = NULL;
	(*map)->size = i;
	close(fd);
}

int	ft_get_start_map(t_temp_map *map)
{
	int	i;

	i = 0;
	while (map->lines[i][0] != ' ' && map->lines[i][0] != '1'
			&& map->lines[i][0] != '0')
		i++;
	return (i);
}
