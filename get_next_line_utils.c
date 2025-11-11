/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:05:22 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/11 22:23:49 by mlorenz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	rest_to_line(char **line, char **rest)
{
	size_t	i;
	size_t	rest_nllen;
	char	*line_ptr;
	char	*rest_ptr;

	if (!rest || !*rest || !**rest)
		return (0);
	line_ptr = *line;
	rest_ptr = *rest;
	rest_nllen = gnl_nllen(rest);
	*line = malloc(rest_nllen + 1);
	if (!*line)
		return (-1);
	while (i++ < rest_nllen)
		*line_ptr++ = *rest_ptr++;
	*line = '\0';
	if (*rest_ptr)
	{
		*rest = rest_ptr;
		return (1);
	}
	free(*rest);
	rest = 0;
	return (0);
}

int	read_to_line(char **line, char **buf, int fd)
{
	size_t	bytes_read;
	size_t	buf_nllen;
	char	*new_line;
	int		ret;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (free(line), -1);
	while (42)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		buf[bytes_read] = '\0';
		if (!bytes_read && !*line)
			return (free(buf), free(line), 0);
		else if (!bytes_read)
			return (1);
		ret = buf_to_line(line, buf);
		if (ret == -1)
			return (free(buf), free(line), -1);
		if (ret == 1)
			return (1);
	}
}

int	buf_to_line(char **line, char **buf)
{
	size_t	buf_nllen;
	char	*new_line;
	char	*new_line_ptr;
	char	*line_ptr;
	char	*buf_ptr;

	buf_nllen = gnl_nllen(*buf);
	new_line = malloc(gnl_strlen(*line) + buf_nllen + 1);
	if (!new_line)
		return (-1);
	new_line_ptr = *new_line;
	line_ptr = *line;
	buf_ptr = *buf;
	while (*line_ptr)
		*new_line_ptr++ = *line_ptr++;
	while (buf_nllen--)
		*new_line_ptr++ = *buf_ptr++;
	*new_line_ptr = '\0';
	free(*line);
	*line = new_line;
	if (*buf_ptr)
		return (1);
	return (0);
}

int	buf_to_rest(char **buf, char **rest)
{
	char	*buf_ptr;

	buf_ptr = *buf;
	while (*buf_ptr != '\n')
		buf_ptr++;
}

size_t	gnl_strlen(char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (*s++)
		i++;
	return (i);
}

size_t	gnl_nllen(char *s)
{
	size_t	i;

	i = 0;
	while (*s++)
	{
		i++;
		if (*s == '\n')
			return (i + 1);
	}
	return (i);
}
