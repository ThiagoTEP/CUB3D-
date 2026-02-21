/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setters_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:34:04 by thevaris          #+#    #+#             */
/*   Updated: 2026/02/20 16:34:05 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

static void	init_doors(t_mlx *win)
{
	int		i;
	int		j;
	int		count;
	t_door	*doors;

	count = 0;
	i = 0;
	while (i < win->map->height)
	{
		j = 0;
		while (j < win->map->width)
		{
			if (win->map->coord[i][j] == DOOR_CHAR)
				count++;
			j++;
		}
		i++;
	}
	win->map->door_count = count;
	if (count == 0)
	{
		win->map->doors = NULL;
		return ;
	}
	doors = ft_calloc(sizeof(t_door), count);
	if (!doors)
		return ;
	count = 0;
	i = 0;
	while (i < win->map->height)
	{
		j = 0;
		while (j < win->map->width)
		{
			if (win->map->coord[i][j] == DOOR_CHAR)
			{
				doors[count].x = j;
				doors[count].y = i;
				doors[count].frame = 0;
				doors[count].timer = 0.0;
				doors[count].state = DOOR_CLOSED;
				count++;
			}
			j++;
		}
		i++;
	}
	win->map->doors = doors;
}

float	ft_set_player(t_mlx *win, char **map)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (map[++i] != NULL)
	{
		while (map[i][j] != '\0' && map[i][j] != 'S'
			&& map[i][j] != 'N' && map[i][j] != 'W' && map[i][j] != 'E')
			j++;
		if (map[i][j] != '\0')
			break ;
		j = 0;
	}
	win->player->x = (float) j * SQUARE + PLAYER_SIZE;
	win->player->y = (float) i * SQUARE + PLAYER_SIZE;
	if (map[i][j] == 'S')
		return (1.570796);
	if (map[i][j] == 'N')
		return (4.712389);
	if (map[i][j] == 'W')
		return (3.141593);
	return (0);
}

void	set_up_win(t_mlx *win, t_temp_map *map)
{
	win->mlx_connect = 0;
	win->mlx_win = 0;
	win->map = 0;
	win->texture_nbr = 0;
	win->map = ft_calloc(sizeof(t_map), 1);
	win->map->coord = get_final_map(map);
	win->color_top = ft_get_colors(map, 'F');
	win->color_bot = ft_get_colors(map, 'C');
	win->player = ft_calloc(sizeof(t_player), 1);
	win->north_texture.path = get_texture_path(map, 'N');
	win->south_texture.path = get_texture_path(map, 'S');
	win->west_texture.path = get_texture_path(map, 'W');
	win->east_texture.path = get_texture_path(map, 'E');
	win->map->height = get_map_size(win->map->coord);
	win->map->width = ft_strlen(win->map->coord[0]);
	win->player->player_angle = ft_set_player(win, win->map->coord);
	win->player->player_delta_x = cos(win->player->player_angle) * 7;
	win->player->player_delta_y = sin(win->player->player_angle) * 7;
	init_doors(win);
}
