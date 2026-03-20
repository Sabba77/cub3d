/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spaces.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:00:00 by tisabbat          #+#    #+#             */
/*   Updated: 2026/03/20 12:41:35 by sabba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	skip_spaces(char *line, int index)
{
	while (line[index] == ' ')
		index++;
	return (index);
}

int	line_is_only_spaces(char *line)
{
	int	index;

	index = 0;
	while (line[index] != '\0')
	{
		if (line[index] != ' ')
			return (0);
		index++;
	}
	return (1);
}
