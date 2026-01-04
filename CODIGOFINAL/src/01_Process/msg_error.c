/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   msg_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:14:15 by thevaris          #+#    #+#             */
/*   Updated: 2026/01/04 20:14:16 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

void	print_error(const char *msg)
{
	int	len;

	if (!msg)
		return ;
	len = 0;
	while (msg[len])
		len++;
	write(2, msg, len);
}

void	error_message_cont(int error_code)
{
	if (error_code == -8)
		print_error("Missing newline\n");
	if (error_code == -9)
		print_error("Missing textures\n");
	if (error_code == -10)
		print_error("Invalid texture\n");
	if (error_code == -11)
		print_error("Error in colors or assets\n");
	if (error_code == -12)
		print_error("Error with the player\n");
	if (error_code == -13)
		print_error("Error with the map\n");
	if (error_code == -14)
		print_error("Open map\n");
	if (error_code == -15)
		print_error("Error in ft_calloc\n");
	if (error_code == -16)
		print_error("Invalid ext.\n");
	if (error_code == -17)
		print_error("Error in textures\n");
}

int	error_message(int error_code, t_temp_map *map)
{
	if (map)
		free_map_parse(&map);
	print_error("Error\n");
	if (error_code == -1)
		print_error("Invalid file\n");
	if (error_code == -2)
		print_error("Cant open this file\n");
	if (error_code == -3)
		print_error("To many colors\n");
	if (error_code == -4)
		print_error("Error in colors\n");
	if (error_code == -5)
		print_error("Missing colors\n");
	if (error_code == -6)
		print_error("Colors must be from 0 to 255\n");
	if (error_code == -7)
		print_error("Invalid characters\n");
	if (error_code < -7)
		error_message_cont(error_code);
	exit(EXIT_FAILURE);
}
