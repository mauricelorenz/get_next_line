/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 22:40:05 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/07 16:22:32 by mlorenz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*rest;
	static char	*rest_orig;
	char		buf[BUFFER_SIZE + 1];
	char		*buf_ptr;
	char		*line;
	char		*line_orig;
	int			all_app_ret;
	int			read_ret;

	line = 0;
	line_orig = 0;
	if (rest)
	{
		all_app_ret = alloc_append(&line, &rest_orig);
		if (all_app_ret == 1)
			return (line);
		if (all_app_ret == -1)
			return (free(rest_orig), (char *)0);
	}
	while (42)
	{
		read_ret = read(fd, buf, BUFFER_SIZE);
		buf[read_ret] = '\0';
		buf_ptr = buf;
		all_app_ret = alloc_append(&line, &buf_ptr);
		if (all_app_ret == -1)
			return (0);
		if (all_app_ret == 1)
		{
			rest = malloc(null_safe_strlen(buf_ptr) + 1);
			if (!rest)
				return (free(line_orig), (char *)0);
			rest_orig = rest;
			while (*buf_ptr)
				*rest++ = *buf_ptr++;
			*rest = '\0';
			return (line);
		}
	}
	return (0);
}
