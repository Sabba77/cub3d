/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 16:00:00 by sabba             #+#    #+#             */
/*   Updated: 2026/03/20 13:19:31 by sabba            ###   ########.fr       */
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

int	render_static_frame(t_cub *cub, t_mlx *mlx)
{
	int	x;
	int	y;
	int	color;

	y = 0;
	while (y < mlx->win_height)
	{
		x = 0;
		if (y < mlx->win_height / 2)
			color = cub->ceiling_color;
		else
			color = cub->floor_color;
		while (x < mlx->win_width)
		{
			put_pixel(&mlx->frame, x, y, color);
			x++;
		}
		y++;
	}
	return (0);
}
