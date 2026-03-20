/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visual.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 16:00:00 by sabba             #+#    #+#             */
/*   Updated: 2026/03/20 13:38:46 by sabba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

void	destroy_visual(t_mlx *mlx)
{
	destroy_textures(mlx);
	if (mlx->frame.img_ptr != NULL)
		mlx_destroy_image(mlx->mlx_ptr, mlx->frame.img_ptr);
	if (mlx->win_ptr != NULL)
		mlx_destroy_window(mlx->mlx_ptr, mlx->win_ptr);
	if (mlx->mlx_ptr != NULL)
	{
		mlx_destroy_display(mlx->mlx_ptr);
		free(mlx->mlx_ptr);
	}
	ft_bzero(mlx, sizeof(t_mlx));
}

static int	init_frame(t_mlx *mlx)
{
	mlx->frame.img_ptr = mlx_new_image(mlx->mlx_ptr,
			mlx->win_width, mlx->win_height);
	if (mlx->frame.img_ptr == NULL)
		return (1);
	mlx->frame.data = mlx_get_data_addr(mlx->frame.img_ptr,
			&mlx->frame.bpp, &mlx->frame.line_len, &mlx->frame.endian);
	if (mlx->frame.data == NULL)
		return (1);
	return (0);
}

static int	init_visual(t_mlx *mlx)
{
	mlx->mlx_ptr = mlx_init();
	if (mlx->mlx_ptr == NULL)
		return (print_error("MLX init failed"));
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr,
			mlx->win_width, mlx->win_height, "cub3D");
	if (mlx->win_ptr == NULL)
	{
		destroy_visual(mlx);
		return (print_error("Cannot create window"));
	}
	if (init_frame(mlx))
	{
		destroy_visual(mlx);
		return (print_error("Cannot create frame image"));
	}
	if (init_textures(mlx))
	{
		destroy_visual(mlx);
		return (print_error("Cannot load textures"));
	}
	return (0);
}

int	start_visual_test(t_cub *cub)
{
	t_mlx	mlx;

	ft_bzero(&mlx, sizeof(t_mlx));
	mlx.win_width = WIN_WIDTH;
	mlx.win_height = WIN_HEIGHT;
	mlx.cub = cub;
	init_player(&mlx);
	if (init_visual(&mlx))
		return (1);
	if (render_scene(&mlx))
	{
		destroy_visual(&mlx);
		return (print_error("Cannot render initial scene"));
	}
	mlx_loop_hook(mlx.mlx_ptr, render_loop, &mlx);
	mlx_hook(mlx.win_ptr, 2, 1L << 0, handle_key, &mlx);
	mlx_hook(mlx.win_ptr, 3, 1L << 1, handle_key_release, &mlx);
	mlx_hook(mlx.win_ptr, 17, 0, close_window, &mlx);
	mlx_expose_hook(mlx.win_ptr, expose_frame, &mlx);
	mlx_loop(mlx.mlx_ptr);
	destroy_visual(&mlx);
	return (0);
}
