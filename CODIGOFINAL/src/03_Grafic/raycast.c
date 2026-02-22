/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:15:14 by thevaris          #+#    #+#             */
/*   Updated: 2026/02/22 17:42:45 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

static int	is_wall(t_mlx *w, int x, int y)
{
	if (x < 0 || x >= w->map->width || y < 0 || y >= w->map->height)
		return (1);
	return (w->map->coord[y][x] == '1');
}

void	init_h(t_mlx *w, t_ray *r, float ra)
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

void	init_v(t_mlx *w, t_ray *r, float ra)
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

void	cast(t_mlx *w, t_ray *r)
{
	while (r->dof < 64)
	{
		r->mx = (int)(r->rx / SQUARE);
		r->my = (int)(r->ry / SQUARE);
		if (is_wall(w, r->mx, r->my))
			break ;
		r->rx += r->xo;
		r->ry += r->yo;
		r->dof++;
	}
}

void	get_h_hit(t_mlx *w, float ra, float *x, float *y)
{
	t_ray	r;

	init_h(w, &r, ra);
	cast(w, &r);
	*x = r.rx;
	*y = r.ry;
}
