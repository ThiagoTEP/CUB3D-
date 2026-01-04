/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:15:46 by thevaris          #+#    #+#             */
/*   Updated: 2026/01/04 20:15:47 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

int	ft_circle_normalizer(float *ra)
{
	if (*ra < 0)
		*ra += 2 * PI;
	if (*ra > 2 * PI)
		*ra -= 2 * PI;
	return (SUCCESS);
}

char	*ft_copy_line(char *map, int max_line)
{
	int		i;
	char	*line;

	i = 0;
	line = NULL;
	line = ft_calloc(sizeof(char), max_line + 1);
	while (map[i] != '\0' && map[i] != '\n')
	{
		line[i] = map[i];
		if (map[i] == ' ')
			line[i] = '0';
		i++;
	}
	while (i < max_line)
	{
		line[i] = '0';
		i++;
	}
	line[i] = '\0';
	return (line);
}

int	rgb_to_int(int red, int green, int blue)
{
	if (red < 0)
		red = 0;
	if (red > 255)
		red = 255;
	if (green < 0)
		green = 0;
	if (green > 255)
		green = 255;
	if (blue < 0)
		blue = 0;
	if (blue > 255)
		blue = 255;
	return ((red << 16) | (green << 8) | blue);
}
