/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_data.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:00:00 by tisabbat          #+#    #+#             */
/*   Updated: 2026/03/20 12:41:35 by sabba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	free_map_lines(char **map)
{
	int	index;

	index = 0;
	if (map == NULL)
		return ;
	while (map[index] != NULL)
	{
		free(map[index]);
		index++;
	}
	free(map);
}

void	init_cub(t_cub *cub)
{
	cub->tex_no = NULL;
	cub->tex_so = NULL;
	cub->tex_we = NULL;
	cub->tex_ea = NULL;
	cub->floor_color = 0;
	cub->ceiling_color = 0;
	cub->has_floor = 0;
	cub->has_ceiling = 0;
	cub->map = NULL;
	cub->map_height = 0;
	cub->player_x = -1;
	cub->player_y = -1;
	cub->player_dir = 0;
}

void	free_cub(t_cub *cub)
{
	free(cub->tex_no);
	free(cub->tex_so);
	free(cub->tex_we);
	free(cub->tex_ea);
	free_map_lines(cub->map);
	init_cub(cub);
}

int	validate_required_data(t_cub *cub, char **error)
{
	if (cub->tex_no == NULL || cub->tex_so == NULL)
		return (set_error(error, "Missing NO or SO texture"));
	if (cub->tex_we == NULL || cub->tex_ea == NULL)
		return (set_error(error, "Missing WE or EA texture"));
	if (cub->has_floor == 0 || cub->has_ceiling == 0)
		return (set_error(error, "Missing F or C color"));
	if (cub->map_height == 0)
		return (set_error(error, "Map is missing"));
	return (0);
}
