/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:05:22 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/11 18:03:42 by mlorenz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	rest_to_line(char **line, char **rest)
{
	size_t	i;
	size_t	rest_nllen;
	char	*line_ptr;
	char	*rest_ptr;

	if (!rest || !*rest || !**rest)
		return (0);
	line_ptr = *line;
	rest_ptr = *rest;
	rest_nllen = gnl_nllen(rest);
	*line = malloc(rest_nllen + 1);
	if (!*line)
		return (-1);
	while (i++ < rest_nllen)
		*line_ptr++ = *rest_ptr++;
	*line = '\0';
	if (*rest_ptr)
	{
		*rest = rest_ptr;
		return (1);
	}
	free(*rest);
	rest = 0;
	return (0);
}

size_t	gnl_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

size_t	gnl_nllen(char *s)
{
	size_t	i;

	i = 0;
	while (*s++)
	{
		i++;
		if (*s == '\n')
			return (i + 1);
	}
	return (i);
}
