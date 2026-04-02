/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabbat <tisabbat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 16:00:00 by sabba             #+#    #+#             */
/*   Updated: 2026/04/02 11:33:28 by tisabbat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*pixel;
	int		index;

	if (x < 0 || y < 0)
		return ;
	index = y * img->line_len;
	index += x * (img->bpp / 8);
	pixel = img->data + index;
	*(unsigned int *)pixel = color;
}

static void	fill_row(t_img *img, int y, int width, int color)
{
	int	x;

	x = 0;
	while (x < width)
	{
		((unsigned int *)(img->data + (y * img->line_len)))[x]
			= (unsigned int)color;
		x++;
	}
}

int	render_static_frame(t_cub *cub, t_mlx *mlx)
{
	int			y;
	int			color;

	y = 0;
	while (y < mlx->win_height)
	{
		if (y < mlx->win_height / 2)
			color = cub->ceiling_color;
		else
			color = cub->floor_color;
		fill_row(&mlx->frame, y, mlx->win_width, color);
		y++;
	}
	return (0);
}
