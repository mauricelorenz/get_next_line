/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:00:21 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/18 15:55:16 by mlorenz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*rest;
	int			ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	buf = NULL;
	if (rest)
	{
		if (!handle_rest(&rest, &line))
			return (NULL);
		if (line && has_nl(line))
			return (line);
	}
	while (1)
	{
		ret = handle_read(&rest, &line, &buf, fd);
		if (ret == 0)
			return (NULL);
		if (ret == 1)
			return (line);
	}
}

int	handle_read(char **rest, char **line, char **buf, int fd)
{
	ssize_t	tmp_n;

	*buf = malloc(BUFFER_SIZE + 1);
	if (!*buf)
		return (free_and_null(line), 0);
	tmp_n = read(fd, *buf, BUFFER_SIZE);
	if (tmp_n == -1)
		return (free_and_null(buf), free_and_null(line), 0);
	if (!tmp_n && (!*line || !**line))
		return (free_and_null(buf), 0);
	if (!tmp_n)
		return (free_and_null(buf), 1);
	*(*buf + tmp_n) = '\0';
	if (!malloc_and_append(line, *buf, len_to_char(*line, '\0'),
			len_to_char(*buf, '\n')))
		return (free_and_null(buf), free_and_null(line), 0);
	if (tmp_n == BUFFER_SIZE && !has_nl(*buf))
		return (free_and_null(buf), 2);
	if (!malloc_and_copy(rest, *buf + len_to_char(*buf, '\n'), 0,
			len_to_char(*buf, '\0') - len_to_char(*buf, '\n')))
		return (free_and_null(buf), free_and_null(line), 0);
	return (free_and_null(buf), 1);
}

int	handle_rest(char **rest, char **line)
{
	size_t	tmp_n;

	if (has_nl(*rest))
		tmp_n = len_to_char(*rest, '\n');
	else
		tmp_n = len_to_char(*rest, '\0');
	if (tmp_n)
		if (!malloc_and_copy(line, *rest, 0, tmp_n))
			return (free_and_null(rest), 0);
	if (*(*rest + tmp_n))
	{
		if (!malloc_and_copy(rest, *rest + tmp_n, len_to_char(*rest, '\0'),
				len_to_char(*rest, '\0') - tmp_n))
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
	ft_memcpy(new_dst, *dst, dst_len);
	ft_memcpy(new_dst + dst_len, src, src_len);
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
	ft_memcpy(new_dst, src, src_len);
	*(new_dst + src_len) = '\0';
	free(*dst);
	*dst = new_dst;
	return (1);
}
