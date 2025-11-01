/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 22:40:05 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/01 21:54:27 by mlorenz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	size_t	loop_count;
	char	*buf;
	char	*buf_orig;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return((char *)0);
	while (read(fd, buf, BUFFER_SIZE))
	{
		
	}
}
