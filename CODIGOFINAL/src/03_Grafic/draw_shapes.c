/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_shapes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:15:03 by thevaris          #+#    #+#             */
/*   Updated: 2026/01/04 20:15:04 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void	draw_square(t_img *img, int x, int y, int color)
{
	int	start_x;
	int	start_y;
	int	i;
	int	j;

	start_x = x * SQUARE;
	start_y = y * SQUARE;
	i = 0;
	while (i < SQUARE)
	{
		j = 0;
		while (j < SQUARE)
		{
			if (i > 0 && j > 0)
				my_pixel_put(img, start_x + j, start_y + i, color);
			j++;
		}
		i++;
	}
}

void	ft_update_player(int px, int py, t_img *img, t_mlx *win)
{
	float	y;
	float	x;
	int		size;

	(void)win;
	size = PLAYER_SIZE;
	y = 0;
	while (y < size && y + py < HEIGHT)
	{
		x = 0;
		while (x < size && x + px < WIDTH)
		{
			if (x > 0 && y > 0)
				my_pixel_put(img, x + px - PLAYER_SIZE / 2,
					y + py - PLAYER_SIZE / 2, 0x0000F0);
			x++;
		}
		y++;
	}
}
