/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:35:34 by thevaris          #+#    #+#             */
/*   Updated: 2026/02/20 16:35:44 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

t_door	*get_door_at(t_mlx *win, int x, int y)
{
	int	i;

	i = 0;
	while (i < win->map->door_count)
	{
		if (win->map->doors[i].x == x && win->map->doors[i].y == y)
			return (&win->map->doors[i]);
		i++;
	}
	return (NULL);
}

static void	advance_frame(t_door *door)
{
	if (door->state == DOOR_OPENING)
	{
		door->frame++;
		if (door->frame >= DOOR_FRAMES - 1)
		{
			door->frame = DOOR_FRAMES - 1;
			door->state = DOOR_OPEN;
		}
	}
	else if (door->state == DOOR_CLOSING)
	{
		door->frame--;
		if (door->frame <= 0)
		{
			door->frame = 0;
			door->state = DOOR_CLOSED;
		}
	}
}

void	update_all_doors(t_mlx *win, double delta_time)
{
	int		i;
	t_door	*door;

	i = 0;
	while (i < win->map->door_count)
	{
		door = &win->map->doors[i];
		if (door->state == DOOR_OPENING || door->state == DOOR_CLOSING)
		{
			door->timer += delta_time;
			if (door->timer >= (1.0 / DOOR_FPS))
			{
				door->timer = 0.0;
				advance_frame(door);
			}
		}
		i++;
	}
}

void	toggle_nearby_door(t_mlx *win)
{
	int		i;
	float	px;
	float	py;
	float	dx;
	float	dy;
	t_door	*door;

	px = win->player->x / SQUARE;
	py = win->player->y / SQUARE;
	i = 0;
	while (i < win->map->door_count)
	{
		door = &win->map->doors[i];
		dx = px - (door->x + 0.5f);
		dy = py - (door->y + 0.5f);
		if ((dx * dx + dy * dy) <= 6.25f)
		{
			if (door->state == DOOR_CLOSED || door->state == DOOR_CLOSING)
				door->state = DOOR_OPENING;
			else if (door->state == DOOR_OPEN || door->state == DOOR_OPENING)
				door->state = DOOR_CLOSING;
			return ;
		}
		i++;
	}
}

void	draw_door_wall(t_mlx *win, float distance, int column,
		float wall_x, float hit_x, float hit_y)
{
	int				line_h;
	int				line_start;
	t_tex			tex;
	t_texture_vars	vars;
	t_door			*door;
	float			open_frac;
	int				tx;

	door = get_door_at(win, (int)(hit_x / SQUARE), (int)(hit_y / SQUARE));
	open_frac = 0.0f;
	if (door)
		open_frac = (float)door->frame / (float)(DOOR_FRAMES - 1);
	if (open_frac >= 1.0f)
		return ;
	if (!win->door_tex.mlx_img || !win->door_tex.addr)
		tex = win->west_texture;
	else
		tex = win->door_tex;
	tx = ((int)(wall_x) + (int)(open_frac * 64.0f)) % 64;
	if (tx < 0)
		tx += 64;
	line_h = (SQUARE * HEIGHT) / distance;
	vars.ty_step = 64.0f / (float)line_h;
	vars.ty_offset = 0.0f;
	if (line_h > HEIGHT)
	{
		vars.ty_offset = ((float)line_h - HEIGHT) / 2.0f;
		line_h = HEIGHT;
	}
	line_start = (HEIGHT / 2) - (line_h / 2);
	vars.y = -1;
	vars.ty = vars.ty_step * vars.ty_offset;
	vars.tx = tx;
	while (++vars.y < line_h)
	{
		int	color;
		color = get_pixel_color(&tex, ((int)vars.tx) % SQUARE, (int)(vars.ty));
		if (color != -1)
			my_pixel_put(&win->img, column, line_start + vars.y, color);
		vars.ty += vars.ty_step;
	}
}
