/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:55:00 by sabba             #+#    #+#             */
/*   Updated: 2026/03/20 12:54:19 by sabba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player_char(char c)
{
	if (c == 'N' || c == 'S')
		return (1);
	if (c == 'E' || c == 'W')
		return (1);
	return (0);
}

int	is_map_char(char c)
{
	if (c == '0' || c == '1')
		return (1);
	if (c == ' ' || is_player_char(c))
		return (1);
	return (0);
}

char	map_get_cell(t_cub *cub, int y, int x)
{
	int	line_len;

	if (y < 0 || y >= cub->map_height)
		return (' ');
	if (x < 0)
		return (' ');
	line_len = (int)ft_strlen(cub->map[y]);
	if (x >= line_len)
		return (' ');
	return (cub->map[y][x]);
}
