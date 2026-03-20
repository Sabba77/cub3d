/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:55:00 by sabba             #+#    #+#             */
/*   Updated: 2026/03/20 12:54:19 by sabba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	has_open_neighbor(t_cub *cub, int y, int x)
{
	if (map_get_cell(cub, y - 1, x) == ' ')
		return (1);
	if (map_get_cell(cub, y + 1, x) == ' ')
		return (1);
	if (map_get_cell(cub, y, x - 1) == ' ')
		return (1);
	if (map_get_cell(cub, y, x + 1) == ' ')
		return (1);
	return (0);
}

static int	validate_player(t_cub *cub, int y, int x, char **error)
{
	char	cell;

	cell = map_get_cell(cub, y, x);
	if (!is_player_char(cell))
		return (0);
	if (cub->player_dir != 0)
		return (set_error(error, "Map must contain exactly one player"));
	cub->player_dir = cell;
	cub->player_x = x;
	cub->player_y = y;
	return (0);
}

static int	validate_row(t_cub *cub, int y, char **error)
{
	int		x;
	char	cell;

	x = 0;
	while (cub->map[y][x] != '\0')
	{
		cell = cub->map[y][x];
		if (!is_map_char(cell))
			return (set_error(error, "Map contains invalid characters"));
		if (validate_player(cub, y, x, error))
			return (1);
		if (cell == '0' || is_player_char(cell))
		{
			if (has_open_neighbor(cub, y, x))
				return (set_error(error, "Map is not closed by walls"));
		}
		x++;
	}
	return (0);
}

int	validate_map(t_cub *cub, char **error)
{
	int	y;

	cub->player_x = -1;
	cub->player_y = -1;
	cub->player_dir = 0;
	y = 0;
	while (y < cub->map_height)
	{
		if (validate_row(cub, y, error))
			return (1);
		y++;
	}
	if (cub->player_dir == 0)
		return (set_error(error, "Map must contain exactly one player"));
	return (0);
}
