/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 18:52:00 by thevaris          #+#    #+#             */
/*   Updated: 2026/02/22 18:52:00 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

static void	start_textures(t_mlx *win, t_tex *texture)
{
	if (texture->path == NULL)
	{
		print_error("Error\nError in texture path\n");
		ft_cleanup_and_exit(win);
	}
	texture->mlx_img = mlx_xpm_file_to_image(win->mlx_connect,
			texture->path, &texture->width, &texture->height);
	if (texture->mlx_img == NULL)
	{
		print_error("Error\nError in texture path\n");
		ft_cleanup_and_exit(win);
	}
	texture->addr = mlx_get_data_addr(texture->mlx_img,
			&texture->bpp, &texture->line_len,
			&texture->endian);
}

static void	start_door_texture(t_mlx *win)
{
	char	*path;

	path = ft_strdup("./Textures/door_closed.xpm");
	if (!path)
		return ;
	win->door_tex.mlx_img = mlx_xpm_file_to_image(win->mlx_connect,
			path, &win->door_tex.width, &win->door_tex.height);
	free(path);
	if (!win->door_tex.mlx_img)
	{
		print_error("Warning: door_closed.xpm not found, using west texture\n");
		return ;
	}
	win->door_tex.addr = mlx_get_data_addr(win->door_tex.mlx_img,
			&win->door_tex.bpp, &win->door_tex.line_len,
			&win->door_tex.endian);
}

void	start_all_textures(t_mlx *win)
{
	start_textures(win, &win->north_texture);
	start_textures(win, &win->south_texture);
	start_textures(win, &win->east_texture);
	start_textures(win, &win->west_texture);
	start_door_texture(win);
}
