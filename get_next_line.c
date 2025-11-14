/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:00:21 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/14 18:09:21 by mlorenz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*rest;
	size_t		tmp_n;
	char		*tmp_ptr;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = NULL;
	buf = NULL;
	if (rest)
	{
		if (ft_strchr(rest, '\n'))
		{
			// copy rest till \n to line
			tmp_n = null_safe_nllen(rest);
			line = malloc(tmp_n + 1);
			if (!line)
			{
				free(rest);
				return (NULL);
			}
			ft_memcpy(line, rest, tmp_n);
			*(line + tmp_n) = '\0';
			// set rest to index \n + 1 and free old rest
			tmp_ptr = malloc(null_safe_strlen(rest) - tmp_n + 1);
			ft_memcpy(tmp_ptr, rest + tmp_n, null_safe_strlen(rest) - tmp_n);
			*(tmp_ptr + null_safe_strlen(rest) - tmp_n) = '\0';
			free(rest);
			rest = tmp_ptr;
			// return line
			return (line);
		}
		else
		{
			// copy rest till \0 to line
			tmp_n = null_safe_strlen(rest);
			line = malloc(tmp_n + 1);
			if (!line)
			{
				free(rest);
				return (NULL);
			}
			ft_memcpy(line, rest, tmp_n);
			*(line + tmp_n) = '\0';
			// free rest
			free(rest);
			rest = NULL;
		}
	}
	while (1)
	{
		// read to buf
		buf = malloc(BUFFER_SIZE + 1);
		tmp_n = read(fd, buf, BUFFER_SIZE);
		*(buf + BUFFER_SIZE) = '\0';
		// if read size = 0 return 0
		if (!tmp_n && !line)
		{
			free(buf);
			return (NULL);
		}
		if (!tmp_n)
		{
			free(buf);
			return (line);
		}
		// if read_size < BUFFER_SIZE copy buf to line and return line
		if (tmp_n < BUFFER_SIZE)
		{
			tmp_ptr = malloc(null_safe_strlen(line) + tmp_n + 1);
			if (!tmp_ptr)
			{
				free(line);
				free(buf);
				return (NULL);
			}
			ft_memcpy(tmp_ptr, line, null_safe_strlen(line));
			ft_memcpy(tmp_ptr + null_safe_strlen(line), buf, tmp_n);
			*(tmp_ptr + null_safe_strlen(line) + tmp_n) = '\0';
			free(line);
			line = tmp_ptr;
			free(buf);
			buf = NULL;
			return (line);
		}
		if (ft_strchr(buf, '\n'))
		{
			// copy buf till \n to line
			tmp_n = null_safe_nllen(buf);
			tmp_ptr = malloc(null_safe_strlen(line) + tmp_n + 1);
			if (!tmp_ptr)
			{
				free(line);
				free(buf);
				return (NULL);
			}
			ft_memcpy(tmp_ptr, line, null_safe_strlen(line));
			ft_memcpy(tmp_ptr + null_safe_strlen(line), buf, tmp_n);
			*(tmp_ptr + null_safe_strlen(line) + tmp_n) = '\0';
			free(line);
			line = tmp_ptr;
			// copy buf to rest at index \n + 1 and free buf
			rest = malloc(null_safe_strlen(buf) - tmp_n + 1);
			if (!rest)
			{
				free(line);
				free(buf);
				return (NULL);
			}
			ft_memcpy(rest, buf + tmp_n, null_safe_strlen(buf) - tmp_n);
			*(rest + null_safe_strlen(buf) - tmp_n) = '\0';
			free(buf);
			buf = NULL;
			// return line
			return (line);
		}
		else
		{
			tmp_ptr = malloc(null_safe_strlen(line) + tmp_n + 1);
			if (!tmp_ptr)
			{
				free(line);
				free(buf);
				return (NULL);
			}
			ft_memcpy(tmp_ptr, line, null_safe_strlen(line));
			ft_memcpy(tmp_ptr + null_safe_strlen(line), buf, tmp_n);
			*(tmp_ptr + null_safe_strlen(line) + tmp_n) = '\0';
			free(line);
			line = tmp_ptr;
			free(buf);
			buf = NULL;
		}
	}
}
