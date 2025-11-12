/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:05:17 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/12 18:25:30 by mlorenz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*buf;
	char		*line;
	static char	*rest;
	static char	*rest_orig;
	int			ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	line = 0;
	ret = rest_to_line(&line, &rest, &rest_orig);
	if (ret == -1)
		return (0);
	else if (ret == 1)
		return (line);
	ret = read_to_line(&line, &buf, fd);
	if (ret == -1)
		return (0);
	else if (ret == 2)
	{
		ret = buf_to_rest(&buf, &rest);
		rest_orig = rest;
	}
	if (ret == -1)
		return (0);
	return (line);
}
