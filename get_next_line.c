/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:00:21 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/13 14:19:12 by mlorenz          ###   ########.fr       */
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
		return (0);
	line = NULL;
	buf = NULL;
	if (rest)
	{
		if (ft_strchr(rest, '\n'))
		{
			// copy rest till \n to line
			// set rest to index \n + 1 and free old rest
			// return line
		}
		else
		{
			// copy rest till \0 to line
			// free rest
		}
	}
	while (1)
	{
		// read to buf
		// if read size = 0 return 0
		// if read_size < BUFFER_SIZE copy buf to line and return line
		if (ft_strchr(buf, '\n'))
		{
			// copy buf till \n to line
			// copy buf to rest at index \n + 1 and free buf
			// return line
		}
	}
}
