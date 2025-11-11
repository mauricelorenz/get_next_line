/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:05:17 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/11 22:22:40 by mlorenz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*rest;
	int			ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = 0;
	ret = rest_to_line(&line, &rest);
	if (ret == -1)
		return (0);
	else if (ret == 0)
		return (line);
	ret = read_to_line(&line, &rest, fd);
	if (ret == -1)
		return (0);
	else if (ret == 1)
		;
	// read buf
	// if read size = 0 => return 0
	// append buf till \n
	// if buf remains => write to rest and return line
	// else return line
}
