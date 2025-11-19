/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:00:21 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/19 15:54:00 by mlorenz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	buf[BUFFER_SIZE + 1];
	char		*buf_ptr;
	int			ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	buf_ptr = buf;
	if (*buf_ptr)
	{
		if (!handle_rest(buf_ptr, &line))
			return (NULL);
		if (line && has_nl(line))
			return (line);
	}
	while (1)
	{
		ret = handle_read(buf_ptr, &line, fd);
		if (ret == 0)
			return (NULL);
		if (ret == 1)
			return (line);
	}
}

int	handle_read(char *buf_ptr, char **line, int fd)
{
	ssize_t	bytes_read;
	size_t	new_len;

	bytes_read = read(fd, buf_ptr, BUFFER_SIZE);
	if (bytes_read == -1)
		return (free_and_null(line), 0);
	if (!bytes_read && (!*line || !**line))
		return (0);
	if (!bytes_read)
	{
		*buf_ptr = '\0';
		return (1);
	}
	*(buf_ptr + bytes_read) = '\0';
	if (!malloc_and_append(line, buf_ptr, len_to_char(*line, '\0'),
			len_to_char(buf_ptr, '\n')))
		return (free_and_null(line), 0);
	if (bytes_read == BUFFER_SIZE && !has_nl(buf_ptr))
		return (2);
	new_len = len_to_char(buf_ptr, '\0') - len_to_char(buf_ptr, '\n');
	gnl_memmove(buf_ptr, buf_ptr + len_to_char(buf_ptr, '\n'),
		len_to_char(buf_ptr, '\0') - len_to_char(buf_ptr, '\n'));
	*(buf_ptr + new_len) = '\0';
	return (1);
}

int	handle_rest(char *buf_ptr, char **line)
{
	size_t	copy_len;
	size_t	new_len;

	if (has_nl(buf_ptr))
		copy_len = len_to_char(buf_ptr, '\n');
	else
		copy_len = len_to_char(buf_ptr, '\0');
	if (copy_len)
		if (!malloc_and_copy(line, buf_ptr, 0, copy_len))
			return (0);
	new_len = len_to_char(buf_ptr, '\0') - copy_len;
	gnl_memmove(buf_ptr, buf_ptr + copy_len, new_len);
	*(buf_ptr + new_len) = '\0';
	return (1);
}

int	malloc_and_append(char **dst, char *src, size_t dst_len, size_t src_len)
{
	char	*new_dst;

	new_dst = malloc(dst_len + src_len + 1);
	if (!new_dst)
		return (0);
	gnl_memmove(new_dst, *dst, dst_len);
	gnl_memmove(new_dst + dst_len, src, src_len);
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
	gnl_memmove(new_dst, src, src_len);
	*(new_dst + src_len) = '\0';
	free(*dst);
	*dst = new_dst;
	return (1);
}
