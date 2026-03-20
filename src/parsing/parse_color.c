/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 12:55:00 by sabba             #+#    #+#             */
/*   Updated: 2026/03/20 12:54:19 by sabba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	parse_component(char *value, int *index, int *component)
{
	int	number;

	number = 0;
	if (!ft_isdigit(value[*index]))
		return (1);
	while (ft_isdigit(value[*index]))
	{
		number = (number * 10) + (value[*index] - '0');
		if (number > 255)
			return (1);
		(*index)++;
	}
	*component = number;
	return (0);
}

int	parse_color_value(char *value, int *color)
{
	int	index;
	int	r;
	int	g;
	int	b;

	index = skip_spaces(value, 0);
	if (parse_component(value, &index, &r))
		return (1);
	index = skip_spaces(value, index);
	if (value[index] != ',')
		return (1);
	index = skip_spaces(value, index + 1);
	if (parse_component(value, &index, &g))
		return (1);
	index = skip_spaces(value, index);
	if (value[index] != ',')
		return (1);
	index = skip_spaces(value, index + 1);
	if (parse_component(value, &index, &b))
		return (1);
	index = skip_spaces(value, index);
	if (value[index] != '\0')
		return (1);
	*color = (r << 16) | (g << 8) | b;
	return (0);
}
