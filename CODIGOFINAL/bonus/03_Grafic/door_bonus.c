/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:35:34 by thevaris          #+#    #+#             */
/*   Updated: 2026/02/22 18:52:00 by thevaris         ###   ########.fr       */
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

static float	door_dist_sq(t_door *door, float px, float py)
{
	float	dx;
	float	dy;

	dx = px - (door->x + 0.5f);
	dy = py - (door->y + 0.5f);
	return (dx * dx + dy * dy);
}

void	toggle_nearby_door(t_mlx *win)
{
	int		i;
	float	px;
	float	py;
	t_door	*door;

	px = win->player->x / SQUARE;
	py = win->player->y / SQUARE;
	i = 0;
	while (i < win->map->door_count)
	{
		door = &win->map->doors[i];
		if (door_dist_sq(door, px, py) <= 6.25f)
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
