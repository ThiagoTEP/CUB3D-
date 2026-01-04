/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:14:49 by thevaris          #+#    #+#             */
/*   Updated: 2026/01/04 20:14:50 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void	check_next_char(t_temp_map *map, int c, int i)
{
	if ((c == 'S' || c == 'N') && map->lines[i][1] != 'O')
		error_message(-7, map);
	if (c == 'W' && map->lines[i][1] != 'E')
		error_message(-7, map);
	if (c == 'E' && map->lines[i][1] != 'A')
		error_message(-7, map);
	if ((c == 'F' || c == 'C') && map->lines[i][1] != ' ')
		error_message(-7, map);
}

char	*ft_color_special(char *line, int j, int i, t_temp_map *map)
{
	char	*new_line;

	new_line = ft_calloc(sizeof(char), ft_strlen(line) + 2);
	if (!new_line)
		error_message(-15, map);
	while (line[i] != '\0')
	{
		while (line[i] != '\0' && !is_whitespace(line[i]))
		{
			new_line[j] = line[i];
			if ((line[i] == 'F' || line[i] == 'C')
				&& is_whitespace(line[i + 1]))
				new_line[++j] = ' ';
			j++;
			i++;
		}
		while (line[i] != '\0' && !is_whitespace(line[i]))
			new_line[j++] = line[i++];
		while (is_whitespace(line[i]))
			i++;
	}
	new_line[j] = '\0';
	free(line);
	return (new_line);
}
