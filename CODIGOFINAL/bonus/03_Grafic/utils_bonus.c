/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 20:02:04 by thevaris          #+#    #+#             */
/*   Updated: 2026/02/22 20:02:29 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D_bonus.h"

void	get_h_hit(t_mlx *w, float ra, float *x, float *y)
{
	t_ray	r;

	init_h(w, &r, ra);
	cast_ray(w, &r);
	*x = r.rx;
	*y = r.ry;
}

void	get_v_hit(t_mlx *w, float ra, float *x, float *y)
{
	t_ray	r;

	init_v(w, &r, ra);
	cast_ray(w, &r);
	*x = r.rx;
	*y = r.ry;
}
