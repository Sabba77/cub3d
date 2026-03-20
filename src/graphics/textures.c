/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 19:10:00 by sabba             #+#    #+#             */
/*   Updated: 2026/03/20 13:38:46 by sabba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include "mlx.h"

static void	destroy_texture(t_mlx *mlx, t_tex *tex)
{
	if (tex->img_ptr != NULL && mlx->mlx_ptr != NULL)
		mlx_destroy_image(mlx->mlx_ptr, tex->img_ptr);
	ft_bzero(tex, sizeof(t_tex));
}

void	destroy_textures(t_mlx *mlx)
{
	destroy_texture(mlx, &mlx->tex_no);
	destroy_texture(mlx, &mlx->tex_so);
	destroy_texture(mlx, &mlx->tex_we);
	destroy_texture(mlx, &mlx->tex_ea);
}

static int	load_texture(t_mlx *mlx, t_tex *tex, char *path)
{
	tex->img_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, path,
			&tex->width, &tex->height);
	if (tex->img_ptr == NULL)
		return (1);
	tex->data = mlx_get_data_addr(tex->img_ptr,
			&tex->bpp, &tex->line_len, &tex->endian);
	if (tex->data == NULL || tex->width <= 0 || tex->height <= 0)
	{
		mlx_destroy_image(mlx->mlx_ptr, tex->img_ptr);
		ft_bzero(tex, sizeof(t_tex));
		return (1);
	}
	return (0);
}

int	init_textures(t_mlx *mlx)
{
	if (load_texture(mlx, &mlx->tex_no, mlx->cub->tex_no))
		return (1);
	if (load_texture(mlx, &mlx->tex_so, mlx->cub->tex_so))
		return (1);
	if (load_texture(mlx, &mlx->tex_we, mlx->cub->tex_we))
		return (1);
	if (load_texture(mlx, &mlx->tex_ea, mlx->cub->tex_ea))
		return (1);
	return (0);
}
