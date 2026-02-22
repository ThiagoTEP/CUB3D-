/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:33:12 by thevaris          #+#    #+#             */
/*   Updated: 2026/02/22 18:52:00 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"
#include <X11/X.h>
#include <sys/time.h>

static double	get_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0);
}

int	draw(t_mlx *win)
{
	static double	last_time;
	double			now;

	now = get_time_ms();
	if (last_time == 0)
		last_time = now;
	win->delta_time = (now - last_time) / 1000.0;
	last_time = now;
	process_movement(win);
	update_all_doors(win, win->delta_time);
	render_background(&win->img, 0xD3D3D3);
	ft_update_player(win->player->x, win->player->y, &win->img, win);
	ft_vision_angle(win, win->player->x, win->player->y);
	render_background_top_bot(win, &win->img);
	raycaster(win);
	ft_draw_minimap(win);
	mlx_put_image_to_window(win->mlx_connect, win->mlx_win,
		win->img.mlx_img, 0, 0);
	return (0);
}

static void	setup_hooks(t_mlx *win)
{
	mlx_hook(win->mlx_win, KeyPress, KeyPressMask, key_press, win);
	mlx_hook(win->mlx_win, KeyRelease, KeyReleaseMask, key_release, win);
	mlx_hook(win->mlx_win, MotionNotify, PointerMotionMask,
		ft_mouse_move, win);
	mlx_hook(win->mlx_win, 17, 0, ft_close, win);
	mlx_loop_hook(win->mlx_connect, &draw, win);
	mlx_mouse_hide(win->mlx_connect, win->mlx_win);
	mlx_loop(win->mlx_connect);
}

void	render(t_mlx *win)
{
	win->keys.w = 0;
	win->keys.a = 0;
	win->keys.s = 0;
	win->keys.d = 0;
	win->keys.left = 0;
	win->keys.right = 0;
	win->keys.esc = 0;
	win->keys.e = 0;
	win->mouse_init = 0;
	win->delta_time = 0;
	win->mlx_connect = mlx_init();
	win->mlx_win = mlx_new_window(win->mlx_connect, WIDTH, HEIGHT, "Cub3D");
	win->img.mlx_img = mlx_new_image(win->mlx_connect, WIDTH, HEIGHT);
	win->img.addr = mlx_get_data_addr(win->img.mlx_img, &win->img.bpp,
			&win->img.line_len, &win->img.endian);
	start_all_textures(win);
	setup_hooks(win);
}

int	main(int argc, char *argv[])
{
	t_mlx		*win;
	t_temp_map	*map;

	argc--;
	if (argc == 1)
	{
		ft_validations(argv);
		map = ft_calloc(sizeof(t_temp_map), 1);
		map->player = ft_calloc(sizeof(t_player), 1);
		map->size = ft_get_file_size(argv[1], map);
		ft_get_map(&map, argv[1], 0, 0);
		win = ft_calloc(sizeof(t_mlx), 1);
		set_up_win(win, map);
		free_map_parse(&map);
		render(win);
	}
	else if (argc > 1)
		print_error("Error\nOnly one input is accepted\n");
	else
		print_error("Error\nPlease use: ./cub3d_bonus map_file/valid/map\n");
	return (0);
}
