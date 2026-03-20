/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/20 10:00:00 by tisabbat          #+#    #+#             */
/*   Updated: 2026/03/20 12:41:35 by sabba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_error(char **error, char *msg)
{
	if (*error == NULL)
		*error = msg;
	return (1);
}

int	print_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	if (msg != NULL)
	{
		ft_putstr_fd(msg, 2);
		ft_putstr_fd("\n", 2);
	}
	return (1);
}
