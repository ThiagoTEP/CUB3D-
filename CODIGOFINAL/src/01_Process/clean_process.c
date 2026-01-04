/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_process.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:13:55 by thevaris          #+#    #+#             */
/*   Updated: 2026/01/04 20:13:56 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void	free_textures_map(t_mlx *mlx)
{
	free(mlx->west_texture.path);
	free(mlx->east_texture.path);
	free(mlx->south_texture.path);
	free(mlx->north_texture.path);
	if (mlx->map != NULL)
	{
		free_split(mlx->map->coord);
		free(mlx->map);
	}
}

void	ft_cleanup_and_exit(t_mlx *mlx)
{
	if (mlx->mlx_connect != NULL)
	{
		mlx_destroy_image(mlx->mlx_connect, mlx->img.mlx_img);
		if (mlx->north_texture.mlx_img)
			mlx_destroy_image(mlx->mlx_connect, mlx->north_texture.mlx_img);
		if (mlx->south_texture.mlx_img)
			mlx_destroy_image(mlx->mlx_connect, mlx->south_texture.mlx_img);
		if (mlx->east_texture.mlx_img)
			mlx_destroy_image(mlx->mlx_connect, mlx->east_texture.mlx_img);
		if (mlx->west_texture.mlx_img)
			mlx_destroy_image(mlx->mlx_connect, mlx->west_texture.mlx_img);
		if (mlx->mlx_win != NULL)
			mlx_destroy_window(mlx->mlx_connect, mlx->mlx_win);
		mlx_destroy_display(mlx->mlx_connect);
		free(mlx->mlx_connect);
	}
	free_textures_map(mlx);
	if (mlx->player != NULL)
		free(mlx->player);
	free(mlx);
	exit(0);
}

int	ft_close(t_mlx *mlx)
{
	ft_cleanup_and_exit(mlx);
	return (0);
}
