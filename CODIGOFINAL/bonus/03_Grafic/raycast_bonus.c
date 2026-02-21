/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 16:36:05 by thevaris          #+#    #+#             */
/*   Updated: 2026/02/20 16:36:06 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

static int	is_wall(t_mlx *w, int x, int y)
{
	char	c;
	t_door	*door;

	if (x < 0 || x >= w->map->width || y < 0 || y >= w->map->height)
		return (1);
	c = w->map->coord[y][x];
	if (c == '1')
		return (1);
	if (c == DOOR_CHAR)
	{
		door = get_door_at(w, x, y);
		if (!door || door->state == DOOR_CLOSED || door->state == DOOR_CLOSING)
			return (1);
		return (0);
	}
	return (0);
}

static int	is_door_visible(t_mlx *w, int x, int y)
{
	t_door	*door;

	if (x < 0 || x >= w->map->width || y < 0 || y >= w->map->height)
		return (0);
	if (w->map->coord[y][x] != DOOR_CHAR)
		return (0);
	door = get_door_at(w, x, y);
	if (!door || door->state != DOOR_OPEN)
		return (1);
	return (0);
}

static void	init_h(t_mlx *w, t_ray *r, float ra)
{
	float	atan;

	r->dof = 0;
	atan = -1 / tan(ra);
	if (ra > PI && ra != 0)
	{
		r->ry = (((int)w->player->y / SQUARE) * SQUARE) - 0.0001;
		r->yo = -SQUARE;
	}
	else if (ra < PI && ra != PI)
	{
		r->ry = (((int)w->player->y / SQUARE) * SQUARE) + SQUARE;
		r->yo = SQUARE;
	}
	else
	{
		r->rx = w->player->x;
		r->ry = w->player->y;
		r->dof = 64;
		return ;
	}
	r->rx = (w->player->y - r->ry) * atan + w->player->x;
	r->xo = -r->yo * atan;
}

static void	init_v(t_mlx *w, t_ray *r, float ra)
{
	float	ntan;

	r->dof = 0;
	ntan = -tan(ra);
	if (ra > P2 && ra < P3)
	{
		r->rx = (((int)w->player->x / SQUARE) * SQUARE) - 0.001;
		r->xo = -SQUARE;
	}
	else if (ra < P2 || ra > P3)
	{
		r->rx = (((int)w->player->x / SQUARE) * SQUARE) + SQUARE;
		r->xo = SQUARE;
	}
	else
	{
		r->rx = w->player->x;
		r->ry = w->player->y;
		r->dof = 64;
		return ;
	}
	r->ry = (w->player->x - r->rx) * ntan + w->player->y;
	r->yo = -r->xo * ntan;
}

static void	cast_ray(t_mlx *w, t_ray *r)
{
	while (r->dof < 64)
	{
		r->mx = (int)(r->rx / SQUARE);
		r->my = (int)(r->ry / SQUARE);
		if (is_wall(w, r->mx, r->my))
			break ;
		if (is_door_visible(w, r->mx, r->my))
			break ;
		r->rx += r->xo;
		r->ry += r->yo;
		r->dof++;
	}
}

static void	get_h_hit(t_mlx *w, float ra, float *x, float *y)
{
	t_ray	r;

	init_h(w, &r, ra);
	cast_ray(w, &r);
	*x = r.rx;
	*y = r.ry;
}

static void	get_v_hit(t_mlx *w, float ra, float *x, float *y)
{
	t_ray	r;

	init_v(w, &r, ra);
	cast_ray(w, &r);
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
		if (is_door_visible(w, (int)(v->hx / SQUARE), (int)(v->hy / SQUARE)))
		{
			v->line *= cos(w->player->player_angle - v->ra);
			draw_door_wall(w, v->line, v->r, v->wall_x, v->hx, v->hy);
			return ;
		}
	}
	else
	{
		ft_texture_picker(w, v->vx, 'v');
		v->wall_x = v->vy;
		v->line = dv;
		if (is_door_visible(w, (int)(v->vx / SQUARE), (int)(v->vy / SQUARE)))
		{
			v->line *= cos(w->player->player_angle - v->ra);
			draw_door_wall(w, v->line, v->r, v->wall_x, v->vx, v->vy);
			return ;
		}
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
