/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 17:45:00 by thevaris          #+#    #+#             */
/*   Updated: 2026/02/22 17:45:01 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

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
