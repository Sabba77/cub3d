/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabbat <tisabbat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 13:48:29 by tisabbat          #+#    #+#             */
/*   Updated: 2025/01/13 12:30:04 by tisabbat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	slen1;
	size_t	slen2;
	char	*res;

	if (!s1 || !s2)
		return (NULL);
	slen1 = ft_strlen(s1);
	slen2 = ft_strlen(s2);
	res = (char *)malloc(slen1 + slen2 + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, s1, slen1 + 1);
	ft_strlcpy(res + slen1, s2, slen2 + 1);
	return (res);
}
