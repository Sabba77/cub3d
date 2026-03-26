/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 17:10:00 by sabba             #+#    #+#             */
/*   Updated: 2026/03/26 11:34:40 by sabba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_walkable(t_mlx *mlx, double x, double y)
{
	double	radius;
	char	cell;

	radius = 0.24;
	cell = map_get_cell(mlx->cub,
			(int)floor(y - radius), (int)floor(x - radius));
	if (cell == '1' || cell == ' ')
		return (0);
	cell = map_get_cell(mlx->cub,
			(int)floor(y - radius), (int)floor(x + radius));
	if (cell == '1' || cell == ' ')
		return (0);
	cell = map_get_cell(mlx->cub,
			(int)floor(y + radius), (int)floor(x - radius));
	if (cell == '1' || cell == ' ')
		return (0);
	cell = map_get_cell(mlx->cub,
			(int)floor(y + radius), (int)floor(x + radius));
	if (cell == '1' || cell == ' ')
		return (0);
	return (1);
}

static void	move_forward(t_mlx *mlx, double speed)
{
	double	new_x;
	double	new_y;

	new_x = mlx->player.x + mlx->player.dir_x * speed;
	new_y = mlx->player.y + mlx->player.dir_y * speed;
	if (is_walkable(mlx, new_x, mlx->player.y))
		mlx->player.x = new_x;
	if (is_walkable(mlx, mlx->player.x, new_y))
		mlx->player.y = new_y;
}

static void	move_side(t_mlx *mlx, double speed)
{
	double	side_x;
	double	side_y;
	double	new_x;
	double	new_y;

	side_x = -mlx->player.dir_y;
	side_y = mlx->player.dir_x;
	new_x = mlx->player.x + side_x * speed;
	new_y = mlx->player.y + side_y * speed;
	if (is_walkable(mlx, new_x, mlx->player.y))
		mlx->player.x = new_x;
	if (is_walkable(mlx, mlx->player.x, new_y))
		mlx->player.y = new_y;
}

static void	rotate_player(t_mlx *mlx, double angle)
{
	double	old_dir_x;
	double	old_plane_x;
	double	cos_a;
	double	sin_a;

	cos_a = cos(angle);
	sin_a = sin(angle);
	old_dir_x = mlx->player.dir_x;
	old_plane_x = mlx->player.plane_x;
	mlx->player.dir_x = mlx->player.dir_x * cos_a
		- mlx->player.dir_y * sin_a;
	mlx->player.dir_y = old_dir_x * sin_a + mlx->player.dir_y * cos_a;
	mlx->player.plane_x = mlx->player.plane_x * cos_a
		- mlx->player.plane_y * sin_a;
	mlx->player.plane_y = old_plane_x * sin_a + mlx->player.plane_y * cos_a;
}

void	update_player_movement(t_mlx *mlx)
{
	double	m_step;
	double	s_step;
	double	len;

	m_step = mlx->key_w - mlx->key_s;
	s_step = mlx->key_d - mlx->key_a;
	if (m_step != 0 || s_step != 0)
	{
		len = sqrt(m_step * m_step + s_step * s_step);
		if (m_step != 0)
			move_forward(mlx, (m_step / len) * MOVE_SPEED);
		if (s_step != 0)
			move_side(mlx, (s_step / len) * (MOVE_SPEED * 0.75));
	}
	if (mlx->key_left)
		rotate_player(mlx, -ROT_SPEED);
	if (mlx->key_right)
		rotate_player(mlx, ROT_SPEED);
}
