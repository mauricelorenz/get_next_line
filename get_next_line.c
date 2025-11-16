/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:00:21 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/16 13:29:59 by mlorenz          ###   ########.fr       */
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
		{
			tmp_n = null_safe_nllen(rest);
			line = malloc(tmp_n + 1);
			if (!line)
				return (free_and_null(&rest));
			ft_memcpy(line, rest, tmp_n);
			*(line + tmp_n) = '\0';
			if (*(rest + tmp_n))
			{
				tmp_ptr = malloc(null_safe_strlen(rest) - tmp_n + 1);
				if (!tmp_ptr)
					return (free_and_null(&rest), free_and_null(&line));
				ft_memcpy(tmp_ptr, rest + tmp_n, null_safe_strlen(rest) - tmp_n);
				*(tmp_ptr + null_safe_strlen(rest) - tmp_n) = '\0';
				free(rest);
				rest = tmp_ptr;
			}
			else
				free_and_null(&rest);
			return (line);
		}
		else
		{
			tmp_n = null_safe_strlen(rest);
			if (tmp_n)
			{
				line = malloc(tmp_n + 1);
				if (!line)
					return (free_and_null(&rest));
				ft_memcpy(line, rest, tmp_n);
				*(line + tmp_n) = '\0';
			}
			free_and_null(&rest);
		}
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
