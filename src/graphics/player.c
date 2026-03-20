/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 16:40:00 by sabba             #+#    #+#             */
/*   Updated: 2026/03/20 13:19:31 by sabba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_orientation(t_player *player, char dir)
{
	if (dir == 'N')
	{
		player->dir_x = 0.0;
		player->dir_y = -1.0;
		player->plane_x = 0.66;
		player->plane_y = 0.0;
	}
	if (dir == 'S')
	{
		player->dir_x = 0.0;
		player->dir_y = 1.0;
		player->plane_x = -0.66;
		player->plane_y = 0.0;
	}
	if (dir == 'E')
	{
		player->dir_x = 1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = 0.66;
	}
	if (dir == 'W')
	{
		player->dir_x = -1.0;
		player->dir_y = 0.0;
		player->plane_x = 0.0;
		player->plane_y = -0.66;
	}
}

void	init_player(t_mlx *mlx)
{
	mlx->player.x = (double)mlx->cub->player_x + 0.5;
	mlx->player.y = (double)mlx->cub->player_y + 0.5;
	set_orientation(&mlx->player, mlx->cub->player_dir);
}
