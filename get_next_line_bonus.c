/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:10:07 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/18 17:18:03 by mlorenz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*rest[FD_MAX];
	int			ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	buf = NULL;
	if (rest[fd])
	{
		if (!handle_rest(&rest[fd], &line))
			return (NULL);
		if (line && has_nl(line))
			return (line);
	}
	while (1)
	{
		ret = handle_read(&rest[fd], &line, &buf, fd);
		if (ret == 0)
			return (NULL);
		if (ret == 1)
			return (line);
	}
}

int	handle_read(char **rest, char **line, char **buf, int fd)
{
	ssize_t	bytes_read;

	*buf = malloc(BUFFER_SIZE + 1);
	if (!*buf)
		return (free_and_null(line), 0);
	bytes_read = read(fd, *buf, BUFFER_SIZE);
	if (bytes_read == -1)
		return (free_and_null(buf), free_and_null(line), 0);
	if (!bytes_read && (!*line || !**line))
		return (free_and_null(buf), 0);
	if (!bytes_read)
		return (free_and_null(buf), 1);
	*(*buf + bytes_read) = '\0';
	if (!malloc_and_append(line, *buf, len_to_char(*line, '\0'),
			len_to_char(*buf, '\n')))
		return (free_and_null(buf), free_and_null(line), 0);
	if (bytes_read == BUFFER_SIZE && !has_nl(*buf))
		return (free_and_null(buf), 2);
	if (!malloc_and_copy(rest, *buf + len_to_char(*buf, '\n'), 0,
			len_to_char(*buf, '\0') - len_to_char(*buf, '\n')))
		return (free_and_null(buf), free_and_null(line), 0);
	return (free_and_null(buf), 1);
}

int	handle_rest(char **rest, char **line)
{
	size_t	copy_len;

	if (has_nl(*rest))
		copy_len = len_to_char(*rest, '\n');
	else
		copy_len = len_to_char(*rest, '\0');
	if (copy_len)
		if (!malloc_and_copy(line, *rest, 0, copy_len))
			return (free_and_null(rest), 0);
	if (*(*rest + copy_len))
	{
		if (!malloc_and_copy(rest, *rest + copy_len, len_to_char(*rest, '\0'),
				len_to_char(*rest, '\0') - copy_len))
			return (free_and_null(rest), free_and_null(line), 0);
	}
	else
		free_and_null(rest);
	return (1);
}

int	malloc_and_append(char **dst, char *src, size_t dst_len, size_t src_len)
{
	char	*new_dst;

	new_dst = malloc(dst_len + src_len + 1);
	if (!new_dst)
		return (0);
	gnl_memcpy(new_dst, *dst, dst_len);
	gnl_memcpy(new_dst + dst_len, src, src_len);
	*(new_dst + dst_len + src_len) = '\0';
	free(*dst);
	*dst = new_dst;
	return (1);
}

int	malloc_and_copy(char **dst, char *src, size_t dst_len, size_t src_len)
{
	char	*new_dst;

	new_dst = malloc(dst_len + src_len + 1);
	if (!new_dst)
		return (0);
	gnl_memcpy(new_dst, src, src_len);
	*(new_dst + src_len) = '\0';
	free(*dst);
	*dst = new_dst;
	return (1);
}
