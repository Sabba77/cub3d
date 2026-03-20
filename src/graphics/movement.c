/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 17:10:00 by sabba             #+#    #+#             */
/*   Updated: 2026/03/20 13:38:46 by sabba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_walkable(t_mlx *mlx, double x, double y)
{
	int		map_x;
	int		map_y;
	char	cell;

	map_x = (int)floor(x);
	map_y = (int)floor(y);
	cell = map_get_cell(mlx->cub, map_y, map_x);
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

static void	set_key_state(int keycode, t_mlx *mlx, int state)
{
	if (keycode == KEY_W)
		mlx->key_w = state;
	else if (keycode == KEY_S)
		mlx->key_s = state;
	else if (keycode == KEY_A)
		mlx->key_a = state;
	else if (keycode == KEY_D)
		mlx->key_d = state;
	else if (keycode == KEY_LEFT)
		mlx->key_left = state;
	else if (keycode == KEY_RIGHT)
		mlx->key_right = state;
}

static void	apply_key_movement(t_mlx *mlx)
{
	if (mlx->key_w)
		move_forward(mlx, MOVE_SPEED);
	if (mlx->key_s)
		move_forward(mlx, -MOVE_SPEED);
	if (mlx->key_a)
		move_side(mlx, -MOVE_SPEED);
	if (mlx->key_d)
		move_side(mlx, MOVE_SPEED);
	if (mlx->key_left)
		rotate_player(mlx, -ROT_SPEED);
	if (mlx->key_right)
		rotate_player(mlx, ROT_SPEED);
}

int	handle_player_input(int keycode, t_mlx *mlx)
{
	if (keycode != 0)
		set_key_state(keycode, mlx, 1);
	apply_key_movement(mlx);
	return (0);
}

int	handle_player_release(int keycode, t_mlx *mlx)
{
	set_key_state(keycode, mlx, 0);
	return (0);
}
