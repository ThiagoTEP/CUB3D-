/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_move3_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 18:52:00 by thevaris          #+#    #+#             */
/*   Updated: 2026/02/22 20:17:11 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

int	ft_mouse_move(int x, int y, t_mlx *mlx)
{
	int		delta_x;
	float	sensitivity;

	(void)y;
	sensitivity = 0.0025f;
	if (x == H_WIDTH)
		return (0);
	if (!mlx->mouse_init)
	{
		mlx_mouse_move(mlx->mlx_connect, mlx->mlx_win, H_WIDTH, H_HEIGHT);
		mlx->mouse_init = 1;
		return (0);
	}
	delta_x = x - H_WIDTH;
	rotate_player_by(mlx, delta_x * sensitivity);
	mlx_mouse_move(mlx->mlx_connect, mlx->mlx_win, H_WIDTH, H_HEIGHT);
	return (0);
}

void	process_movement(t_mlx *mlx)
{
	float	new_x;
	float	new_y;
	float	temp_x;
	float	temp_y;

	new_x = mlx->player->x;
	new_y = mlx->player->y;
	do_movements(mlx, &new_x, &new_y);
	temp_x = mlx->player->x;
	temp_y = mlx->player->y;
	if (!check_collision(mlx, new_x, temp_y)
		|| check_collision(mlx, temp_x, temp_y))
		mlx->player->x = new_x;
	if (!check_collision(mlx, temp_x, new_y)
		|| check_collision(mlx, temp_x, temp_y))
		mlx->player->y = new_y;
	if (mlx->keys.esc)
		ft_cleanup_and_exit(mlx);
}
