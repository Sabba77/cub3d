/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:00:00 by tisabbat          #+#    #+#             */
/*   Updated: 2026/03/20 12:41:35 by sabba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	has_cub_extension(char *path)
{
	int	length;

	length = (int)ft_strlen(path);
	if (length < 5)
		return (0);
	if (ft_strncmp(path + length - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

static void	trim_newline(char *line)
{
	int	length;

	length = (int)ft_strlen(line);
	if (length > 0 && line[length - 1] == '\n')
		line[length - 1] = '\0';
}

static void	read_lines(int fd, t_cub *cub, t_map_state *state, char **error)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		trim_newline(line);
		process_file_line(line, cub, state, error);
		free(line);
		if (*error != NULL)
			return ;
		line = get_next_line(fd);
	}
}

int	parse_cub_file(char *path, t_cub *cub)
{
	t_map_state	state;
	char		*error;
	int			fd;

	error = NULL;
	state.started = 0;
	state.ended = 0;
	fd = -1;
	if (!has_cub_extension(path))
		set_error(&error, "Map file must have .cub extension");
	if (error == NULL)
		fd = open(path, O_RDONLY);
	if (fd < 0 && error == NULL)
		set_error(&error, "Cannot open map file");
	if (error == NULL)
		read_lines(fd, cub, &state, &error);
	if (fd >= 0)
		close(fd);
	if (error == NULL)
		validate_required_data(cub, &error);
	if (error == NULL)
		validate_map(cub, &error);
	if (error != NULL)
		return (print_error(error));
	return (0);
}
