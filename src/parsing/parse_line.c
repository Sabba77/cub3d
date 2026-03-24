/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:00:00 by tisabbat          #+#    #+#             */
/*   Updated: 2026/03/21 12:59:00 by sabba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	is_config_identifier(char *line)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "SO ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "WE ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "EA ", 3) == 0)
		return (1);
	if (ft_strncmp(line, "F ", 2) == 0)
		return (1);
	if (ft_strncmp(line, "C ", 2) == 0)
		return (1);
	return (0);
}

static int	is_map_line(char *line)
{
	int	index;

	if (line[0] == '\0')
		return (0);
	index = 0;
	while (line[index] != '\0')
	{
		if (!is_map_char(line[index]))
			return (0);
		index++;
	}
	return (1);
}

static int	parse_before_map(char *line, t_cub *cub, t_map_state *state,
			char **error)
{
	int	status;

	if (line[0] == '\0' || line_is_only_spaces(line))
		return (0);
	status = parse_config_line(line, cub, error);
	if (status != 2)
		return (status);
	if (!is_map_line(line))
		return (set_error(error, "Invalid line before map"));
	state->started = 1;
	return (add_map_line(cub, line, error));
}

int	process_file_line(char *line, t_cub *cub, t_map_state *state, char **error)
{
	int	index;

	if (!state->started)
		return (parse_before_map(line, cub, state, error));
	if (line[0] == '\0')
	{
		state->ended = 1;
		return (0);
	}
	if (state->ended)
		return (set_error(error, "Map must be the last block in the file"));
	index = skip_spaces(line, 0);
	if (is_config_identifier(line + index))
		return (set_error(error, "Map must be the last block in the file"));
	if (!is_map_line(line))
		return (set_error(error, "Map contains invalid characters"));
	return (add_map_line(cub, line, error));
}
