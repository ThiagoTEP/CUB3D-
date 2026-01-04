/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_render.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:15:34 by thevaris          #+#    #+#             */
/*   Updated: 2026/01/04 20:15:35 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void	ft_init_vars(t_ray_vars	*vars, t_mlx *win)
{
	vars->r = -1;
	vars->ra = win->player->player_angle - (FOV / 2);
}

int	ft_mod(int n)
{
	if (n < 0)
		n = -n;
	return (n);
}

float	line_length(float x1, float y1, float x2, float y2)
{
	return (sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2)));
}
