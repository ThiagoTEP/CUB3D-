/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validations.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:14:59 by thevaris          #+#    #+#             */
/*   Updated: 2026/01/04 20:15:00 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void	check_bool_final(t_temp_map *map)
{
	first_check(map, 0);
	if (map->valid->so == false || map->valid->no == false
		|| map->valid->we == false || map->valid->ea == false)
		error_message(-9, map);
	if (map->valid->c == false || map->valid->f == false)
		error_message(-5, map);
}

int	is_whitespace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

void	ft_validations(char *argv[])
{
	t_temp_map	*map;

	ft_check_file_name(argv[1]);
	map = ft_calloc(sizeof(t_temp_map), 1);
	map->player = ft_calloc(sizeof(t_player), 1);
	map->size = ft_get_file_size(argv[1], map);
	ft_get_map(&map, argv[1], 0, 0);
	check_bool_final(map);
	col_val(map, -1);
	check_textures(map, 0);
	check_map(map, 0, 0, -1);
	free_map_parse(&map);
}
