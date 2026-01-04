/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_extensions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thevaris <thevaris@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/04 20:14:44 by thevaris          #+#    #+#             */
/*   Updated: 2026/01/04 20:14:45 by thevaris         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../Includes/cub3d.h"

int	check_extension(char *file_name, char *ext, int len)
{
	if (len < 4)
		return (-1);
	if (ft_strncmp(file_name, ext, 5) == 0)
		return (-1);
	while (len > 0 && file_name[len] != '.')
		len--;
	if (ft_strncmp(&file_name[len], ext, 5))
		return (-1);
	if (len > 0 && file_name[len] == '.' && file_name[len - 1] == '/')
		return (-1);
	return (0);
}

int	ft_check_file_name(char *file_name)
{
	int	fd;
	int	len;

	fd = 0;
	len = (int)ft_strlen(file_name);
	if (check_extension(file_name, ".cub", len) == -1)
		return (error_message(-1, NULL));
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (error_message(-2, NULL));
	close(fd);
	return (0);
}
