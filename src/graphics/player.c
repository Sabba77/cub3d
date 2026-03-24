/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 16:40:00 by sabba             #+#    #+#             */
/*   Updated: 2026/03/21 12:49:43 by sabba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_direction(t_player *player, double x, double y)
{
	player->dir_x = x;
	player->dir_y = y;
}

static void	set_plane(t_player *player, double x, double y)
{
	player->plane_x = x;
	player->plane_y = y;
}

static void	set_orientation(t_player *player, char dir)
{
	if (dir == 'N')
	{
		set_direction(player, 0.0, -1.0);
		set_plane(player, 0.66, 0.0);
	}
	else if (dir == 'S')
	{
		set_direction(player, 0.0, 1.0);
		set_plane(player, -0.66, 0.0);
	}
	else if (dir == 'E')
	{
		set_direction(player, 1.0, 0.0);
		set_plane(player, 0.0, 0.66);
	}
	else
	{
		set_direction(player, -1.0, 0.0);
		set_plane(player, 0.0, -0.66);
	}
}

void	init_player(t_mlx *mlx)
{
	mlx->player.x = (double)mlx->cub->player_x + 0.5;
	mlx->player.y = (double)mlx->cub->player_y + 0.5;
	set_orientation(&mlx->player, mlx->cub->player_dir);
}
