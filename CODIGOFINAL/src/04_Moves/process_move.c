/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_move.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:15:41 by thevaris          #+#    #+#             */
/*   Updated: 2026/01/04 20:15:42 by thevaris         ###   ########.fr       */
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

static int	check_collision(t_mlx *mlx, float x, float y)
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

static void	rotate_player_by(t_mlx *mlx, float delta)
{
	mlx->player->player_angle += delta;
	if (mlx->player->player_angle < 0)
		mlx->player->player_angle += 2 * PI;
	if (mlx->player->player_angle > 2 * PI)
		mlx->player->player_angle -= 2 * PI;
	mlx->player->player_delta_x = cos(mlx->player->player_angle) * 7;
	mlx->player->player_delta_y = sin(mlx->player->player_angle) * 7;
}

static void	rotate_player(t_mlx *mlx, float rot_speed)
{
	if (mlx->keys.left)
		rotate_player_by(mlx, -rot_speed);
	if (mlx->keys.right)
		rotate_player_by(mlx, rot_speed);
}

int	ft_mouse_move(int x, int y, t_mlx *mlx)
{
	int		delta_x;
	float	sensitivity;

	(void)y;
	sensitivity = 0.0025f;
	if (!mlx->mouse_init)
	{
		mlx->mouse_last_x = x;
		mlx->mouse_init = 1;
		return (0);
	}
	delta_x = x - mlx->mouse_last_x;
	mlx->mouse_last_x = x;
	rotate_player_by(mlx, delta_x * sensitivity);
	return (0);
}

static void	move_forward_back(t_mlx *mlx, float *x, float *y, float speed)
{
	float	cos_a;
	float	sin_a;

	cos_a = cos(mlx->player->player_angle);
	sin_a = sin(mlx->player->player_angle);
	if (mlx->keys.w)
	{
		*x += cos_a * speed;
		*y += sin_a * speed;
	}
	if (mlx->keys.s)
	{
		*x -= cos_a * speed;
		*y -= sin_a * speed;
	}
}

static void	move_strafe(t_mlx *mlx, float *x, float *y, float speed)
{
	float	cos_a;
	float	sin_a;

	cos_a = cos(mlx->player->player_angle);
	sin_a = sin(mlx->player->player_angle);
	if (mlx->keys.a)
	{
		*x += sin_a * speed * 0.7f;
		*y -= cos_a * speed * 0.7f;
	}
	if (mlx->keys.d)
	{
		*x -= sin_a * speed * 0.7f;
		*y += cos_a * speed * 0.7f;
	}
}

void	process_movement(t_mlx *mlx)
{
	float	new_x;
	float	new_y;
	float	temp_x;
	float	temp_y;

	new_x = mlx->player->x;
	new_y = mlx->player->y;
	rotate_player(mlx, 0.05f);
	move_forward_back(mlx, &new_x, &new_y, 5.0f);
	move_strafe(mlx, &new_x, &new_y, 5.0f);
	temp_x = mlx->player->x;
	temp_y = mlx->player->y;
	if (!check_collision(mlx, new_x, temp_y))
		mlx->player->x = new_x;
	if (!check_collision(mlx, temp_x, new_y))
		mlx->player->y = new_y;
	if (mlx->keys.esc)
		ft_cleanup_and_exit(mlx);
}
