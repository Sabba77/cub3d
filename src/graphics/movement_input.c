/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 12:35:00 by sabba             #+#    #+#             */
/*   Updated: 2026/03/21 12:49:43 by sabba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int	handle_player_input(int keycode, t_mlx *mlx)
{
	if (keycode != 0)
		set_key_state(keycode, mlx, 1);
	update_player_movement(mlx);
	return (0);
}

int	handle_player_release(int keycode, t_mlx *mlx)
{
	set_key_state(keycode, mlx, 0);
	return (0);
}
