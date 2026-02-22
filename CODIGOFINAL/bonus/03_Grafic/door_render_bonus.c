/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 18:52:00 by thevaris          #+#    #+#             */
/*   Updated: 2026/02/22 22:27:05 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

static int	get_tex_pixel(t_tex *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (-1);
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(int *)pixel);
}

static void	draw_door_col(t_mlx *win, t_tex *tex, t_texture_vars *v, int col)
{
	int	line_h;
	int	line_start;
	int	color;
	int	tex_x;

	tex_x = (int)v->tx;
	line_h = (int)v->ty_offset;
	v->ty_step = 64.0f / (float)line_h;
	v->ty = 0.0f;
	if (line_h > HEIGHT)
	{
		v->ty = ((float)line_h - HEIGHT) / 2.0f * v->ty_step;
		line_h = HEIGHT;
	}
	line_start = (HEIGHT / 2) - (line_h / 2);
	v->y = -1;
	while (++v->y < line_h)
	{
		color = get_tex_pixel(tex, tex_x % SQUARE, (int)v->ty);
		if (color != -1)
			my_pixel_put(&win->img, col, line_start + v->y, color);
		v->ty += v->ty_step;
	}
}

void	draw_door_wall(t_mlx *win, float distance, int column, t_door_draw *d)
{
	t_tex			tex;
	t_texture_vars	vars;
	t_door			*door;
	float			open_frac;
	int				tx;

	door = get_door_at(win, (int)(d->hit_x / SQUARE),
			(int)(d->hit_y / SQUARE));
	open_frac = 0.0f;
	if (door)
		open_frac = (float)door->frame / (float)(DOOR_FRAMES - 1);
	if (open_frac >= 1.0f)
		return ;
	if (!win->door_tex.mlx_img || !win->door_tex.addr)
		tex = win->west_texture;
	else
		tex = win->door_tex;
	tx = ((int)(d->wall_x) + (int)(open_frac * 64.0f)) % 64;
	if (tx < 0)
		tx += 64;
	vars.tx = (float)tx;
	vars.ty_offset = (float)((SQUARE * HEIGHT) / distance);
	draw_door_col(win, &tex, &vars, column);
}
