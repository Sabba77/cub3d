/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabbat <tisabbat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 12:18:24 by tisabbat          #+#    #+#             */
/*   Updated: 2025/01/14 09:17:39 by tisabbat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	x;
	size_t	y;

	if (!big && len == 0)
		return (NULL);
	if (*little == '\0')
		return ((char *)big);
	x = 0;
	while (big[x] && x < len)
	{
		y = 0;
		while (little[y] && (x + y) < len)
		{
			if (big[x + y] != little[y])
				break ;
			y++;
		}
		if (!little[y])
			return ((char *)&big[x]);
		x++;
	}
	return (NULL);
}
