/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:35:56 by thevaris          #+#    #+#             */
/*   Updated: 2026/02/22 22:49:17 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	draw_mm_tile(t_img *img, int sx, int sy, int color)
{
	int	y;
	int	x;

	y = 0;
	while (y < MM_TILE)
	{
		x = 0;
		while (x < MM_TILE)
		{
			my_pixel_put(img, x + sx, y + sy, color);
			x++;
		}
		y++;
	}
}

static int	mm_hit_check(t_mlx *win, float x, float y)
{
	int		map_x;
	int		map_y;
	char	c;
	t_door	*door;

	map_x = (int)((x - MM_MARGIN) / MM_TILE);
	map_y = (int)((y - MM_MARGIN) / MM_TILE);
	if (map_x < 0 || map_x >= win->map->width
		|| map_y < 0 || map_y >= win->map->height)
		return (1);
	c = win->map->coord[map_y][map_x];
	if (c == '1')
		return (1);
	if (c == DOOR_CHAR)
	{
		door = get_door_at(win, map_x, map_y);
		if (!door || door->state == DOOR_CLOSED
			|| door->state == DOOR_CLOSING)
			return (1);
	}
	return (0);
}

void	draw_mm_dir_ray(t_mlx *win, float ra)
{
	float	x;
	float	y;
	float	dx;
	float	dy;
	int		i;

	i = 0;
	x = (MM_MARGIN + (win->player->x / SQUARE) * MM_TILE) + MM_P_MARGIN;
	y = (MM_MARGIN + (win->player->y / SQUARE) * MM_TILE) + MM_P_MARGIN;
	dx = cos(ra);
	dy = sin(ra);
	while (i < win->map->width * SQUARE)
	{
		if (mm_hit_check(win, x, y))
			break ;
		my_pixel_put(&win->img, (int)x, (int)y, 0xAA00FF);
		x += dx;
		y += dy;
		i++;
	}
}

static int	get_tile_color(t_mlx *win, int x, int y)
{
	if (win->map->coord[y][x] == '1')
		return (0x333333);
	if (win->map->coord[y][x] == DOOR_CHAR)
		return (0x8B4513);
	return (0xAAAAAA);
}

void	draw_mm_tiles(t_mlx *win)
{
	int	x;
	int	y;
	int	screen_x;
	int	screen_y;

	y = 0;
	while (y < win->map->height)
	{
		x = 0;
		while (x < win->map->width)
		{
			screen_x = (MM_TILE * x) + MM_MARGIN;
			screen_y = (MM_TILE * y) + MM_MARGIN;
			draw_mm_tile(&win->img, screen_x, screen_y,
				get_tile_color(win, x, y));
			x++;
		}
		y++;
	}
}
