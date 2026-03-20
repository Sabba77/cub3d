/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 16:40:00 by sabba             #+#    #+#             */
/*   Updated: 2026/03/20 13:38:46 by sabba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

static void	init_ray(t_mlx *mlx, t_ray *ray, int x)
{
	ray->camera_x = 2.0 * x / (double)mlx->win_width - 1.0;
	ray->dir_x = mlx->player.dir_x + mlx->player.plane_x * ray->camera_x;
	ray->dir_y = mlx->player.dir_y + mlx->player.plane_y * ray->camera_x;
	ray->map_x = (int)mlx->player.x;
	ray->map_y = (int)mlx->player.y;
	if (ray->dir_x == 0.0)
		ray->delta_x = 1e30;
	else
		ray->delta_x = fabs(1.0 / ray->dir_x);
	if (ray->dir_y == 0.0)
		ray->delta_y = 1e30;
	else
		ray->delta_y = fabs(1.0 / ray->dir_y);
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

static t_tex	*select_texture(t_mlx *mlx, t_ray *ray)
{
	if (ray->side == 0 && ray->dir_x < 0.0)
		return (&mlx->tex_we);
	if (ray->side == 0)
		return (&mlx->tex_ea);
	if (ray->dir_y < 0.0)
		return (&mlx->tex_no);
	return (&mlx->tex_so);
}

static int	get_texel_color(t_tex *tex, int x, int y)
{
	char	*pixel;
	int		index;

	if (x < 0)
		x = 0;
	if (y < 0)
		y = 0;
	if (x >= tex->width)
		x = tex->width - 1;
	if (y >= tex->height)
		y = tex->height - 1;
	index = y * tex->line_len + x * (tex->bpp / 8);
	pixel = tex->data + index;
	return (*(unsigned int *)pixel);
}

static void	draw_wall_column(t_mlx *mlx, t_ray *ray, int x)
{
	t_tex	*tex;
	double	wall_x;
	int		tex_x;
	int		y;
	int		tex_y;

	tex = select_texture(mlx, ray);
	if (ray->side == 0)
		wall_x = mlx->player.y + ray->wall_dist * ray->dir_y;
	else
		wall_x = mlx->player.x + ray->wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	tex_x = (int)(wall_x * tex->width);
	if (ray->side == 0 && ray->dir_x > 0.0)
		tex_x = tex->width - tex_x - 1;
	if (ray->side == 1 && ray->dir_y < 0.0)
		tex_x = tex->width - tex_x - 1;
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)((y - ray->draw_start) * (double)tex->height
				/ (ray->draw_end - ray->draw_start + 1));
		put_pixel(&mlx->frame, x, y, get_texel_color(tex, tex_x, tex_y));
		y++;
	}
}

static void	draw_ray(t_mlx *mlx, t_ray *ray, int x)
{
	int	line_height;

	if (ray->side == 0)
		ray->wall_dist = ray->side_x - ray->delta_x;
	else
		ray->wall_dist = ray->side_y - ray->delta_y;
	if (ray->wall_dist <= 0.0)
		ray->wall_dist = 0.1;
	line_height = (int)(mlx->win_height / ray->wall_dist);
	ray->draw_start = -line_height / 2 + mlx->win_height / 2;
	ray->draw_end = line_height / 2 + mlx->win_height / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	if (ray->draw_end >= mlx->win_height)
		ray->draw_end = mlx->win_height - 1;
	draw_wall_column(mlx, ray, x);
}

int	render_scene(t_mlx *mlx)
{
	t_ray	ray;
	int		x;

	if (render_static_frame(mlx->cub, mlx))
		return (1);
	x = 0;
	while (x < mlx->win_width)
	{
		init_ray(mlx, &ray, x);
		run_dda(mlx, &ray);
		draw_ray(mlx, &ray, x);
		x++;
	}
	mlx_put_image_to_window(mlx->mlx_ptr, mlx->win_ptr, mlx->frame.img_ptr, 0, 0);
	mlx_do_sync(mlx->mlx_ptr);
	return (0);
}
