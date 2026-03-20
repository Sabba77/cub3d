/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_store.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:55:00 by sabba             #+#    #+#             */
/*   Updated: 2026/03/20 12:54:19 by sabba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	add_map_line(t_cub *cub, char *line, char **error)
{
	char	**new_map;
	char	*new_line;
	int	index;

	new_line = ft_strdup(line);
	if (new_line == NULL)
		return (set_error(error, "Memory allocation failed"));
	new_map = malloc(sizeof(char *) * (cub->map_height + 2));
	if (new_map == NULL)
	{
		free(new_line);
		return (set_error(error, "Memory allocation failed"));
	}
	index = 0;
	while (index < cub->map_height)
	{
		new_map[index] = cub->map[index];
		index++;
	}
	new_map[cub->map_height] = new_line;
	new_map[cub->map_height + 1] = NULL;
	free(cub->map);
	cub->map = new_map;
	cub->map_height++;
	return (0);
}
