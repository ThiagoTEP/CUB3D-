/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_process.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:13:59 by thevaris          #+#    #+#             */
/*   Updated: 2026/01/04 20:14:00 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void	free_map_parse(t_temp_map **map)
{
	int	i;

	i = 0;
	if (map)
	{
		while (i <= (*map)->size)
		{
			free((*map)->lines[i]);
			i++;
		}
		if ((*map)->lines)
			free((*map)->lines);
		if ((*map)->valid)
			free((*map)->valid);
		if ((*map)->player)
			free((*map)->player);
		free(*map);
	}
}

void	free_split(char **str)
{
	int	j;

	j = 0;
	while (str[j] != NULL)
		free(str[j++]);
	free(str);
}

void	ft_free_pack(t_temp_map *map, char **temp)
{
	free_split(temp);
	error_message(-10, map);
}

void	ft_end_gnl(int fd, t_temp_map *map, char *line)
{
	print_error("Error\nFile to big\n");
	get_next_line(-1);
	free(map->player);
	free(map);
	free(line);
	close(fd);
	exit(EXIT_FAILURE);
}
