/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_and_textures.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:15:30 by thevaris          #+#    #+#             */
/*   Updated: 2026/01/04 20:15:31 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void	ft_texture_picker(t_mlx *win, float ray_point, char c)
{
	if (c == 'h')
	{
		if (ray_point > win->player->y)
			win->texture_nbr = 0;
		else
			win->texture_nbr = 1;
	}
	else
	{
		if (ray_point > win->player->x)
			win->texture_nbr = 2;
		else
			win->texture_nbr = 3;
	}
}

static void	ft_texture_setter(t_mlx *win, t_tex *texture_to_use, float *tx)
{
	if (win->texture_nbr == 0)
	{
		*texture_to_use = win->north_texture;
		*tx = 63 - *tx;
	}
	else if (win->texture_nbr == 1)
		*texture_to_use = win->south_texture;
	else if (win->texture_nbr == 2)
		*texture_to_use = win->west_texture;
	else if (win->texture_nbr == 3)
	{
		*texture_to_use = win->east_texture;
		*tx = 63 - *tx;
	}
}

static void	ft_wall_limits(int *line_h, float *ty_offset)
{
	if (*line_h > HEIGHT)
	{
		*ty_offset = ((float)*line_h - HEIGHT) / 2;
		*line_h = HEIGHT;
	}
}

void	draw_3d_walls(t_mlx *win, float distance, int column, float hx)
{
	int				line_h;
	int				line_start;
	t_tex			texture_to_use;
	t_texture_vars	vars;

	line_h = (SQUARE * HEIGHT) / distance;
	vars.ty_step = 64 / (float)line_h;
	vars.ty_offset = 0;
	ft_wall_limits(&line_h, &vars.ty_offset);
	line_start = (HEIGHT / 2) - (line_h / 2);
	vars.y = -1;
	vars.ty = vars.ty_step * vars.ty_offset;
	vars.tx = (int)(hx) % 64;
	ft_texture_setter(win, &texture_to_use, &vars.tx);
	while (++vars.y < line_h)
	{
		my_pixel_put(&win->img, column, line_start + vars.y,
			get_pixel_color(&texture_to_use,
				((int)vars.tx) % SQUARE, (int)(vars.ty)));
		vars.ty += vars.ty_step;
	}
}
