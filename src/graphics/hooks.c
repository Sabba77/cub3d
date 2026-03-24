/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 16:00:00 by sabba             #+#    #+#             */
/*   Updated: 2026/03/21 13:22:30 by sabba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

int	close_window(t_mlx *mlx)
{
	if (mlx->mlx_ptr != NULL)
		mlx_loop_end(mlx->mlx_ptr);
	return (0);
}

int	handle_key(int keycode, t_mlx *mlx)
{
	if (keycode == KEY_ESC)
		return (close_window(mlx));
	return (handle_player_input(keycode, mlx));
}

int	handle_key_release(int keycode, t_mlx *mlx)
{
	return (handle_player_release(keycode, mlx));
}

int	expose_frame(t_mlx *mlx)
{
	if (render_scene(mlx))
		return (close_window(mlx));
	return (0);
}

int	render_loop(t_mlx *mlx)
{
	if (!should_render_frame())
		return (0);
	update_player_movement(mlx);
	if (render_scene(mlx))
		return (close_window(mlx));
	return (0);
}
