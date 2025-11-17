/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:00:21 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/17 19:44:46 by mlorenz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*rest;
	ssize_t		tmp_n;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	buf = NULL;
	if (rest)
	{
		if (!handle_rest(&rest, &line))
			return (NULL);
		if (line && ft_strchr(line, '\n'))
			return (line);
	}
	while (1)
	{
		buf = malloc(BUFFER_SIZE + 1);
		if (!buf)
			return (free_and_null(&line));
		tmp_n = read(fd, buf, BUFFER_SIZE);
		if (tmp_n == -1)
			return (free_and_null(&buf), free_and_null(&line));
		if (!tmp_n && (!line || !*line))
			return (free_and_null(&buf));
		if (!tmp_n)
			return (free_and_null(&buf), line);
		*(buf + tmp_n) = '\0';
		if (!malloc_and_append(&line, buf, null_safe_strlen(line), null_safe_nllen(buf)))
			return (free_and_null(&buf), free_and_null(&line));
		if (tmp_n == BUFFER_SIZE && !ft_strchr(buf, '\n'))
			free_and_null(&buf);
		else
		{
			if (!malloc_and_copy(&rest, buf + null_safe_nllen(buf), 0, null_safe_strlen(buf) - null_safe_nllen(buf)))
				return (free_and_null(&buf), free_and_null(&line));
			return (free_and_null(&buf), line);
		}
	}
}

int	handle_rest(char **rest, char **line)
{
	size_t	tmp_n;

	if (ft_strchr(*rest, '\n'))
		tmp_n = null_safe_nllen(*rest);
	else
		tmp_n = null_safe_strlen(*rest);
	if (tmp_n)
		if (!malloc_and_copy(line, *rest, 0, tmp_n))
			return (free_and_null(rest), 0);
	if (*(*rest + tmp_n))
	{
		if (!malloc_and_copy(rest, *rest + tmp_n, null_safe_strlen(*rest), null_safe_strlen(*rest) - tmp_n))
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
