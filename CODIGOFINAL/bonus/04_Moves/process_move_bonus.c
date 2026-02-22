/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_move_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:36:12 by thevaris          #+#    #+#             */
/*   Updated: 2026/02/22 18:52:00 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

static void	set_key(int keycode, t_keys *keys, int value)
{
	if (keycode == XK_w || keycode == XK_Up)
		keys->w = value;
	else if (keycode == XK_s || keycode == XK_Down)
		keys->s = value;
	else if (keycode == XK_a)
		keys->a = value;
	else if (keycode == XK_d)
		keys->d = value;
	else if (keycode == XK_Left)
		keys->left = value;
	else if (keycode == XK_Right)
		keys->right = value;
	else if (keycode == XK_Escape)
		keys->esc = value;
	else if (keycode == XK_e)
		keys->e = value;
}

int	key_press(int keycode, t_mlx *mlx)
{
	if (keycode == XK_e)
		toggle_nearby_door(mlx);
	set_key(keycode, &mlx->keys, 1);
	return (0);
}

int	key_release(int keycode, t_mlx *mlx)
{
	set_key(keycode, &mlx->keys, 0);
	return (0);
}

int	tile_is_solid(t_mlx *mlx, int mx, int my)
{
	char	c;
	t_door	*door;

	if (mx < 0 || mx >= mlx->map->width || my < 0 || my >= mlx->map->height)
		return (1);
	c = mlx->map->coord[my][mx];
	if (c == '1')
		return (1);
	if (c == DOOR_CHAR)
	{
		door = get_door_at(mlx, mx, my);
		if (!door || door->state == DOOR_CLOSED || door->state == DOOR_CLOSING)
			return (1);
	}
	return (0);
}

int	check_collision(t_mlx *mlx, float x, float y)
{
	float	margin;

	margin = 10.0f;
	if (tile_is_solid(mlx, (int)((x - margin) / SQUARE),
		(int)((y - margin) / SQUARE)))
		return (1);
	if (tile_is_solid(mlx, (int)((x + margin) / SQUARE),
		(int)((y - margin) / SQUARE)))
		return (1);
	if (tile_is_solid(mlx, (int)((x - margin) / SQUARE),
		(int)((y + margin) / SQUARE)))
		return (1);
	if (tile_is_solid(mlx, (int)((x + margin) / SQUARE),
		(int)((y + margin) / SQUARE)))
		return (1);
	return (0);
}
