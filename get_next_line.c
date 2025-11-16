/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:00:21 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/16 19:57:08 by mlorenz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*rest;
	ssize_t		tmp_n;
	char		*tmp_ptr;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	buf = NULL;
	if (rest)
	{
		if (ft_strchr(rest, '\n'))
			tmp_n = null_safe_nllen(rest);
		else
			tmp_n = null_safe_strlen(rest);
		if (tmp_n)
			if (!malloc_and_copy(&line, rest, 0, tmp_n))
				return (NULL);
		if (*(rest + tmp_n))
		{
			if (!malloc_and_copy(&rest, rest + tmp_n, null_safe_strlen(rest), null_safe_strlen(rest) - tmp_n))
				return (NULL);
		}
		else
			free_and_null(&rest);
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
		if (tmp_n < BUFFER_SIZE)
		{
			tmp_ptr = malloc(null_safe_strlen(line) + null_safe_nllen(buf) + 1);
			if (!tmp_ptr)
				return (free_and_null(&buf), free_and_null(&line));
			ft_memcpy(tmp_ptr, line, null_safe_strlen(line));
			ft_memcpy(tmp_ptr + null_safe_strlen(line), buf, null_safe_nllen(buf));
			*(tmp_ptr + null_safe_strlen(line) + null_safe_nllen(buf)) = '\0';
			free(line);
			line = tmp_ptr;
			rest = malloc(null_safe_strlen(buf) - null_safe_nllen(buf) + 1);
			if (!rest)
				return (free_and_null(&buf), free_and_null(&line));
			ft_memcpy(rest, buf + null_safe_nllen(buf), null_safe_strlen(buf) - null_safe_nllen(buf));
			*(rest + null_safe_strlen(buf) - null_safe_nllen(buf)) = '\0';
			return (free_and_null(&buf), line);
		}
		if (ft_strchr(buf, '\n'))
		{
			tmp_n = null_safe_nllen(buf);
			tmp_ptr = malloc(null_safe_strlen(line) + tmp_n + 1);
			if (!tmp_ptr)
				return (free_and_null(&buf), free_and_null(&line));
			ft_memcpy(tmp_ptr, line, null_safe_strlen(line));
			ft_memcpy(tmp_ptr + null_safe_strlen(line), buf, tmp_n);
			*(tmp_ptr + null_safe_strlen(line) + tmp_n) = '\0';
			free(line);
			line = tmp_ptr;
			rest = malloc(null_safe_strlen(buf) - tmp_n + 1);
			if (!rest)
				return (free_and_null(&buf), free_and_null(&line));
			ft_memcpy(rest, buf + tmp_n, null_safe_strlen(buf) - tmp_n);
			*(rest + null_safe_strlen(buf) - tmp_n) = '\0';
			return (free_and_null(&buf), line);
		}
		else
		{
			tmp_ptr = malloc(null_safe_strlen(line) + tmp_n + 1);
			if (!tmp_ptr)
				return (free_and_null(&buf), free_and_null(&line));
			ft_memcpy(tmp_ptr, line, null_safe_strlen(line));
			ft_memcpy(tmp_ptr + null_safe_strlen(line), buf, tmp_n);
			*(tmp_ptr + null_safe_strlen(line) + tmp_n) = '\0';
			free(line);
			line = tmp_ptr;
			free_and_null(&buf);
		}
	}
}

char	*malloc_and_copy(char **dst, char *src, size_t dst_len, size_t src_len)
{
	char	*new_dst;

	new_dst = malloc(dst_len + src_len + 1);
	if (!new_dst)
		return (free_and_null(dst), free_and_null(&src));
	ft_memcpy(new_dst, src, src_len);
	*(new_dst + src_len) = '\0';
	free(*dst);
	*dst = new_dst;
	return (*dst);
}
