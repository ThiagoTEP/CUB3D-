/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_render.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 17:45:05 by thevaris          #+#    #+#             */
/*   Updated: 2026/02/22 17:45:06 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

static void	get_v_hit(t_mlx *w, float ra, float *x, float *y)
{
	t_ray	r;

	init_v(w, &r, ra);
	cast(w, &r);
	*x = r.rx;
	*y = r.ry;
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
		ft_texture_picker(w, v->hy, 'h');
		v->wall_x = v->hx;
		v->line = dh;
	}
	else
	{
		ft_texture_picker(w, v->vx, 'v');
		v->wall_x = v->vy;
		v->line = dv;
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
