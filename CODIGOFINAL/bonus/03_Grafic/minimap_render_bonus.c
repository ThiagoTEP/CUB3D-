/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 18:52:00 by thevaris          #+#    #+#             */
/*   Updated: 2026/02/22 18:52:00 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	draw_mm_player(t_mlx *win)
{
	int	py;
	int	px;

	px = MM_MARGIN + ((win->player->x / SQUARE) * MM_TILE);
	py = MM_MARGIN + ((win->player->y / SQUARE) * MM_TILE);
	draw_mm_tile(&win->img, px, py, 0xFF0000);
}

void	draw_mm_dir(t_mlx *win)
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

void	ft_draw_minimap(t_mlx *win)
{
	draw_mm_tiles(win);
	draw_mm_player(win);
	draw_mm_dir(win);
}
