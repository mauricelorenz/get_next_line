/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 13:37:39 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/11 15:41:58 by mlorenz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	*rest;
	static char	*rest_ptr;
	char		*buf;
	char		*buf_ptr;
	size_t		bytes_read;

	line = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	buf = malloc(BUFFER_SIZE + 1);
	if (rest_ptr)
	{
		create_or_grow_str(&line, rest_ptr, '\n');
		str_append(&line, &rest_ptr, '\n');
		if (*rest_ptr)
			return (free(buf), line);
	}
	while (42)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (!bytes_read)
		{
			if (!line || !*line)
				return (free(buf), free(line), (char *)0);
			else
				return (free(buf), line);
		}
		buf[bytes_read] = '\0';
		buf_ptr = buf;
		create_or_grow_str(&line, buf_ptr, '\n');
		str_append(&line, &buf_ptr, '\n');
		if (*buf_ptr || bytes_read < BUFFER_SIZE)
		{
			new_rest(&rest, buf_ptr);
			rest_ptr = rest;
			return (free(buf), line);
		}
	}
	return (free(buf), free(line), (char *)0);
}
