/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabbat <tisabbat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 16:40:00 by sabba             #+#    #+#             */
/*   Updated: 2026/04/02 11:33:28 by tisabbat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

#define TARGET_RAY_COLUMNS 1024

static void	init_ray_delta(t_ray *ray)
{
	if (ray->dir_x == 0.0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0.0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1.0 / ray->dir_y);
}

static void	init_ray_step(t_mlx *mlx, t_ray *ray)
{
	if (ray->dir_x < 0.0)
	{
		ray->step_x = -1;
		ray->side_x = (mlx->player.x - ray->map_x) * ray->delta_x;
	}
	else
	{
		ray->step_x = 1;
		ray->side_x = (ray->map_x + 1.0 - mlx->player.x) * ray->delta_x;
	}
	if (ray->dir_y < 0.0)
	{
		ray->step_y = -1;
		ray->side_y = (mlx->player.y - ray->map_y) * ray->delta_y;
	}
	else
	{
		ray->step_y = 1;
		ray->side_y = (ray->map_y + 1.0 - mlx->player.y) * ray->delta_y;
	}
}

static void	init_ray(t_mlx *mlx, t_ray *ray, int x)
{
	ray->camera_x = 2.0 * x / (double)mlx->win_width - 1.0;
	ray->dir_x = mlx->player.dir_x + mlx->player.plane_x * ray->camera_x;
	ray->dir_y = mlx->player.dir_y + mlx->player.plane_y * ray->camera_x;
	ray->map_x = (int)mlx->player.x;
	ray->map_y = (int)mlx->player.y;
	init_ray_delta(ray);
	init_ray_step(mlx, ray);
	ray->hit = 0;
}

static void	run_dda(t_mlx *mlx, t_ray *ray)
{
	char	cell;

	while (ray->hit == 0)
	{
		if (ray->side_x < ray->side_y)
		{
			ray->side_x += ray->delta_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_y += ray->delta_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		cell = map_get_cell(mlx->cub, ray->map_y, ray->map_x);
		if (cell == '1' || cell == ' ')
			ray->hit = 1;
	}
}

int	render_scene(t_mlx *mlx)
{
	t_ray	ray;
	int		x;
	int		ray_step;
	int		ray_x;

	if (render_static_frame(mlx->cub, mlx))
		return (1);
	ray_step = 1;
	if (mlx->win_width > TARGET_RAY_COLUMNS)
		ray_step = mlx->win_width / TARGET_RAY_COLUMNS;
	x = 0;
	while (x < mlx->win_width)
	{
		ray_x = x + (ray_step / 2);
		if (ray_x >= mlx->win_width)
			ray_x = mlx->win_width - 1;
		init_ray(mlx, &ray, ray_x);
		run_dda(mlx, &ray);
		draw_ray(mlx, &ray, x, ray_step);
		x += ray_step;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr,
		mlx->frame.img_ptr, 0, 0);
	return (0);
}
