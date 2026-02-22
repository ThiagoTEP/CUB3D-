/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:15:41 by thevaris          #+#    #+#             */
/*   Updated: 2026/02/22 17:44:39 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

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
}

int	key_press(int keycode, t_mlx *mlx)
{
	set_key(keycode, &mlx->keys, 1);
	return (0);
}

int	key_release(int keycode, t_mlx *mlx)
{
	set_key(keycode, &mlx->keys, 0);
	return (0);
}

int	check_collision(t_mlx *mlx, float x, float y)
{
	int		mx;
	int		my;
	float	margin;

	margin = 10.0f;
	mx = (int)((x - margin) / SQUARE);
	my = (int)((y - margin) / SQUARE);
	if (mx < 0 || mx >= mlx->map->width || my < 0 || my >= mlx->map->height)
		return (1);
	if (mlx->map->coord[my][mx] == '1')
		return (1);
	mx = (int)((x + margin) / SQUARE);
	my = (int)((y + margin) / SQUARE);
	if (mx < 0 || mx >= mlx->map->width || my < 0 || my >= mlx->map->height)
		return (1);
	return (mlx->map->coord[my][mx] == '1');
}

void	rotate_player_by(t_mlx *mlx, float delta)
{
	mlx->player->player_angle += delta;
	if (mlx->player->player_angle < 0)
		mlx->player->player_angle += 2 * PI;
	if (mlx->player->player_angle > 2 * PI)
		mlx->player->player_angle -= 2 * PI;
	mlx->player->player_delta_x = cos(mlx->player->player_angle) * 7;
	mlx->player->player_delta_y = sin(mlx->player->player_angle) * 7;
}
