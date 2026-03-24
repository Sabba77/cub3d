/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:00:00 by tisabbat          #+#    #+#             */
/*   Updated: 2026/03/21 12:24:20 by sabba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_texture_path(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	return (0);
}

static int	parse_texture(char *line, int id_len, char **dst, char **error)
{
	int		start;
	int		end;
	char	*path;

	if (*dst != NULL)
		return (set_error(error, "Duplicated texture identifier"));
	start = skip_spaces(line, id_len);
	end = (int)ft_strlen(line);
	while (end > start && line[end - 1] == ' ')
		end--;
	if (start >= end)
		return (set_error(error, "Texture path is missing"));
	path = ft_substr(line, start, end - start);
	if (path == NULL)
		return (set_error(error, "Memory allocation failed"));
	if (ft_strchr(path, ' ') != NULL || check_texture_path(path))
	{
		free(path);
		return (set_error(error, "Invalid texture path"));
	}
	*dst = path;
	return (0);
}

static int	parse_texture_line(char *line, t_cub *cub, char **error)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (parse_texture(line, 2, &cub->tex_no, error));
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (parse_texture(line, 2, &cub->tex_so, error));
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (parse_texture(line, 2, &cub->tex_we, error));
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (parse_texture(line, 2, &cub->tex_ea, error));
	return (2);
}

static int	parse_color_line(char *line, t_cub *cub, char **error)
{
	if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (cub->has_floor)
			return (set_error(error, "Duplicated floor color"));
		if (parse_color_value(line + 1, &cub->floor_color))
			return (set_error(error, "Invalid floor color"));
		cub->has_floor = 1;
		return (0);
	}
	if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (cub->has_ceiling)
			return (set_error(error, "Duplicated ceiling color"));
		if (parse_color_value(line + 1, &cub->ceiling_color))
			return (set_error(error, "Invalid ceiling color"));
		cub->has_ceiling = 1;
		return (0);
	}
	return (2);
}

int	parse_config_line(char *line, t_cub *cub, char **error)
{
	int	index;
	int	status;

	index = skip_spaces(line, 0);
	status = parse_texture_line(line + index, cub, error);
	if (status != 2)
		return (status);
	return (parse_color_line(line + index, cub, error));
}
