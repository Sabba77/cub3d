/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 12:35:00 by sabba             #+#    #+#             */
/*   Updated: 2026/03/25 10:49:57 by sabba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

static void	draw_pixels(t_mlx *mlx, t_ray *ray, t_tex *tex, int x_data[2])
{
	int	y;
	int	tex_y;
	int	line_h;
	int	x;
	int	tex_x;

	x = x_data[0];
	tex_x = x_data[1];
	line_h = (int)(mlx->win_height / ray->wall_dist);
	y = ray->draw_start;
	while (y <= ray->draw_end)
	{
		tex_y = (int)((y - mlx->win_height / 2.0 + line_h / 2.0)
				* (double)tex->height / line_h);
		put_pixel(&mlx->frame, x, y, get_texel_color(tex, tex_x, tex_y));
		y++;
	}
}

static void	draw_wall_column(t_mlx *mlx, t_ray *ray, int x)
{
	t_tex	*tex;
	double	wall_x;
	int		x_data[2];

	tex = select_texture(mlx, ray);
	if (ray->side == 0)
		wall_x = mlx->player.y + ray->wall_dist * ray->dir_y;
	else
		wall_x = mlx->player.x + ray->wall_dist * ray->dir_x;
	wall_x -= floor(wall_x);
	x_data[0] = x;
	x_data[1] = (int)(wall_x * tex->width);
	if (ray->side == 0 && ray->dir_x > 0.0)
		x_data[1] = tex->width - x_data[1] - 1;
	if (ray->side == 1 && ray->dir_y < 0.0)
		x_data[1] = tex->width - x_data[1] - 1;
	draw_pixels(mlx, ray, tex, x_data);
}

void	draw_ray(t_mlx *mlx, t_ray *ray, int x)
{
	int	line_height;

	if (ray->side == 0)
		ray->wall_dist = (ray->map_x - mlx->player.x
				+ (1 - ray->step_x) / 2) / ray->dir_x;
	else
		ray->wall_dist = (ray->map_y - mlx->player.y
				+ (1 - ray->step_y) / 2) / ray->dir_y;
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
