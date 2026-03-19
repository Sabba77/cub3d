/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabbat <tisabbat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 09:28:58 by tisabbat          #+#    #+#             */
/*   Updated: 2025/01/08 11:11:05 by tisabbat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	x;
	size_t	y;
	size_t	slen;

	slen = ft_strlen(src);
	x = 0;
	y = 0;
	while (dst[x] && x < size)
		x++;
	if (x == size)
		return (size + slen);
	while (src[y] && (x + y + 1) < size)
	{
		dst[x + y] = src[y];
		y++;
	}
	if ((x + y) < size)
		dst[x + y] = '\0';
	return (x + slen);
}
