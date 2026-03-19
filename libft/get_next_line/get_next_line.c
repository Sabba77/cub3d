/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tisabbat <tisabbat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:48:26 by tisabbat          #+#    #+#             */
/*   Updated: 2025/04/17 10:40:43 by tisabbat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_checks_line(char *line, char **buf)
{
	*buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!*buf)
		return (NULL);
	if (!line)
	{
		free(*buf);
		return (NULL);
	}
	return (line);
}

char	*ft_read_line(int fd, char *line)
{
	char	*buf_read;
	char	*tmp_line;
	char	*to_free;
	int		bytes_read;

	tmp_line = ft_checks_line(line, &buf_read);
	bytes_read = 1;
	while (bytes_read > 0)
	{
		if (ft_strchr_gnl(tmp_line, '\n'))
			break ;
		bytes_read = read(fd, buf_read, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buf_read);
			free(tmp_line);
			return (NULL);
		}
		buf_read[bytes_read] = '\0';
		to_free = tmp_line;
		tmp_line = ft_strjoin_gnl(tmp_line, buf_read);
		free(to_free);
	}
	free(buf_read);
	return (tmp_line);
}

char	*ft_extract_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

char	*ft_extract_rest(char *str)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	rest = (char *)malloc(sizeof(char) * (ft_strlen_gnl(str) - i + 1));
	if (!rest)
		return (NULL);
	i++;
	j = 0;
	while (str[i])
		rest[j++] = str[i++];
	rest[j] = '\0';
	free(str);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!rest)
		rest = ft_strdup_gnl("");
	rest = ft_read_line(fd, rest);
	if (!rest || !*rest)
	{
		free(rest);
		rest = NULL;
		return (NULL);
	}
	line = ft_extract_line(rest);
	rest = ft_extract_rest(rest);
	if (!rest || !*rest)
	{
		free(rest);
		rest = NULL;
	}
	return (line);
}
/*
#include <fcntl.h>
#include <stdio.h>
int main()
{
	int fd = open("file.txt",O_RDONLY);
	char *line;
	int i = 5;
	while (i)
	{
		line = get_next_line(fd);
		printf("%s\n",line);
		free(line);
		i--;
	}
}
*/