/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:35:56 by thevaris          #+#    #+#             */
/*   Updated: 2026/02/20 16:35:57 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

static void	draw_mm_tile(t_img *img, int sx, int sy, int color)
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
	int	map_x;
	int	map_y;

	map_x = (int)((x - MM_MARGIN) / MM_TILE);
	map_y = (int)((y - MM_MARGIN) / MM_TILE);
	if (map_x < 0 || map_x >= win->map->width
		|| map_y < 0 || map_y >= win->map->height)
		return (1);
	return (win->map->coord[map_y][map_x] == '1');
}

static void	draw_mm_dir_ray(t_mlx *win, float ra)
{
	int		i;
	int		mm_lim;
	float	x;
	float	y;
	float	dx;
	float	dy;

	i = 0;
	mm_lim = win->map->width * SQUARE;
	x = (MM_MARGIN + (win->player->x / SQUARE) * MM_TILE) + MM_P_MARGIN;
	y = (MM_MARGIN + (win->player->y / SQUARE) * MM_TILE) + MM_P_MARGIN;
	dx = cos(ra);
	dy = sin(ra);
	while (i < mm_lim)
	{
		if (mm_hit_check(win, x, y))
			break ;
		my_pixel_put(&win->img, (int)x, (int)y, 0xAA00FF);
		x += dx;
		y += dy;
		i++;
	}
}

static void	draw_mm_dir(t_mlx *win)
{
	int		i;
	float	start;
	float	step;
	float	ra;

	start = win->player->player_angle - (FOV / 2);
	step = FOV / 30;
	i = 0;
	while (i < 30)
	{
		ra = start + i * step;
		draw_mm_dir_ray(win, ra);
		i++;
	}
}

static void	draw_mm_player(t_mlx *win)
{
	int	py;
	int	px;

	px = MM_MARGIN + ((win->player->x / SQUARE) * MM_TILE);
	py = MM_MARGIN + ((win->player->y / SQUARE) * MM_TILE);
	draw_mm_tile(&win->img, px, py, 0xFF0000);
}

void	ft_draw_minimap(t_mlx *win)
{
	int	x;
	int	y;
	int	screen_x;
	int	screen_y;
	int	color;

	y = 0;
	while (y < win->map->height)
	{
		x = 0;
		while (x < win->map->width)
		{
			screen_x = (MM_TILE * x) + MM_MARGIN;
			screen_y = (MM_TILE * y) + MM_MARGIN;
			if (win->map->coord[y][x] == '1')
				color = 0x333333;
			else if (win->map->coord[y][x] == DOOR_CHAR)
				color = 0x8B4513;
			else
				color = 0xAAAAAA;
			draw_mm_tile(&win->img, screen_x, screen_y, color);
			x++;
		}
		y++;
	}
	draw_mm_player(win);
	draw_mm_dir(win);
}
