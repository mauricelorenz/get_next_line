/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 22:40:05 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/05 23:59:19 by mlorenz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*rest;
	char		buf[BUFFER_SIZE + 1];
	char		*buf_ptr;
	char		*line;
	char		*line_orig;

	rest = 0;
	line = 0;
	buf_ptr = buf;
	if (rest)
	{
		// count to \n or \0
		// realloc memory for line
		// copy to line till \n or \0
		// return if \n found
		// exit if \0 reached
	}
	while (read(fd, buf, BUFFER_SIZE))
	{
		// null terminate buf
		// count to \n or \0 and realloc memory for line
		// copy to line
		// if \n copy remaining buffer to rest and return
		// if \0 reached start again
	}
	return (0);
}
