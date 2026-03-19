/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabbat <tisabbat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:59:18 by tisabbat          #+#    #+#             */
/*   Updated: 2025/04/01 15:02:18 by tisabbat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	*alloc_word(const char *str, char c)
{
	size_t	len;
	char	*word;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	ft_memcpy(word, str, len);
	word[len] = '\0';
	return (word);
}

static void	free_mem(char **arr, size_t n)
{
	while (n--)
		free(arr[n]);
	free(arr);
}

static char	**fill_words(const char *s, char c, size_t word_count)
{
	char	**res;
	size_t	i;

	i = 0;
	res = (char **)malloc(sizeof(char *) * (word_count + 1));
	if (!res)
		return (NULL);
	while (i < word_count)
	{
		while (*s == c)
			s++;
		res[i] = alloc_word(s, c);
		if (!res[i])
		{
			free_mem(res, i);
			return (NULL);
		}
		while (*s && *s != c)
			s++;
		i++;
	}
	res[i] = NULL;
	return (res);
}

char	**ft_split(char const *s, char c)
{
	size_t	word_count;

	if (!s)
		return (NULL);
	word_count = count_words(s, c);
	return (fill_words(s, c, word_count));
}
