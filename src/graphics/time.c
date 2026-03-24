/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabba <sabba@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 13:20:00 by sabba             #+#    #+#             */
/*   Updated: 2026/03/21 13:04:52 by sabba            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <sys/time.h>

long	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL) != 0)
		return (0);
	return ((tv.tv_sec * 1000L) + (tv.tv_usec / 1000L));
}

int	should_render_frame(void)
{
	static long	last_frame_time;
	long		now;

	now = get_time_ms();
	if (now == 0)
		return (0);
	if (last_frame_time != 0 && (now - last_frame_time) < 16)
		return (0);
	last_frame_time = now;
	return (1);
}
