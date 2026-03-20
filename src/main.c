/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:00:00 by tisabbat          #+#    #+#             */
/*   Updated: 2026/03/20 13:05:39 by sabba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;
	int	parse_status;
	int	visual_status;

	if (argc != 2)
		return (print_error("Usage: ./cub3D <map.cub>"));
	init_cub(&cub);
	parse_status = parse_cub_file(argv[1], &cub);
	if (parse_status != 0)
	{
		free_cub(&cub);
		return (1);
	}
	visual_status = start_visual_test(&cub);
	free_cub(&cub);
	if (visual_status != 0)
		return (1);
	return (0);
}
