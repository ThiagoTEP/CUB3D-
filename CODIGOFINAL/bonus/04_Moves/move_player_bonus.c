/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_move2_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 18:52:00 by thevaris          #+#    #+#             */
/*   Updated: 2026/02/22 18:52:00 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

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

static void	rotate_player(t_mlx *mlx, float rot_speed)
{
	if (mlx->keys.left)
		rotate_player_by(mlx, -rot_speed);
	if (mlx->keys.right)
		rotate_player_by(mlx, rot_speed);
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

void	do_movements(t_mlx *mlx, float *nx, float *ny)
{
	rotate_player(mlx, 0.05f);
	move_forward_back(mlx, nx, ny, 5.0f);
	move_strafe(mlx, nx, ny, 5.0f);
}
