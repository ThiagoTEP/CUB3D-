/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_checkers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:14:35 by thevaris          #+#    #+#             */
/*   Updated: 2026/01/04 20:14:37 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

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
		&& c != ' ')
		error_message(-7, map);
	return (0);
}
