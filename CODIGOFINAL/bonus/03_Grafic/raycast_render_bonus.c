/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast2_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 18:52:00 by thevaris          #+#    #+#             */
/*   Updated: 2026/02/22 18:52:00 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

static void	pick_h_wall(t_mlx *w, t_ray_vars *v, float dh, float dv)
{
	t_door_draw	d;

	ft_texture_picker(w, v->hy, 'h');
	v->wall_x = v->hx;
	v->line = dh;
	if (is_door_vis(w, (int)(v->hx / SQUARE), (int)(v->hy / SQUARE)))
	{
		v->line *= cos(w->player->player_angle - v->ra);
		d.wall_x = v->wall_x;
		d.hit_x = v->hx;
		d.hit_y = v->hy;
		draw_door_wall(w, v->line, v->r, &d);
		return ;
	}
	(void)dv;
}

static int	pick_v_wall(t_mlx *w, t_ray_vars *v, float dh, float dv)
{
	t_door_draw	d;

	ft_texture_picker(w, v->vx, 'v');
	v->wall_x = v->vy;
	v->line = dv;
	if (is_door_vis(w, (int)(v->vx / SQUARE), (int)(v->vy / SQUARE)))
	{
		v->line *= cos(w->player->player_angle - v->ra);
		d.wall_x = v->wall_x;
		d.hit_x = v->vx;
		d.hit_y = v->vy;
		draw_door_wall(w, v->line, v->r, &d);
		return (1);
	}
	(void)dh;
	return (0);
}

static void	render_wall(t_mlx *w, t_ray_vars *v)
{
	float	dh;
	float	dv;

	get_h_hit(w, v->ra, &v->hx, &v->hy);
	get_v_hit(w, v->ra, &v->vx, &v->vy);
	dh = line_length(w->player->x, w->player->y, v->hx, v->hy);
	dv = line_length(w->player->x, w->player->y, v->vx, v->vy);
	if (dh < dv)
	{
		pick_h_wall(w, v, dh, dv);
		if (is_door_vis(w, (int)(v->hx / SQUARE), (int)(v->hy / SQUARE)))
			return ;
	}
	else
	{
		if (pick_v_wall(w, v, dh, dv))
			return ;
	}
	v->line *= cos(w->player->player_angle - v->ra);
	draw_3d_walls(w, v->line, v->r, v->wall_x);
}

void	raycaster(t_mlx *w)
{
	t_ray_vars	v;

	ft_init_vars(&v, w);
	while (++v.r < WIDTH && ft_circle_normalizer(&v.ra) == SUCCESS)
	{
		render_wall(w, &v);
		v.ra += DR;
	}
}
