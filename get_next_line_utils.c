/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 22:40:08 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/07 16:49:51 by mlorenz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	alloc_append(char **line, char **to_append)
{
	char	*new;
	char	*new_orig;
	char	*line_orig;

	line_orig = *line;
	new = malloc(null_safe_strlen(*line) + find_newline(*to_append) + 1);
	if (!new)
		return (free(line_orig), -1);
	new_orig = new;
	if (*line)
	{
		while (**line)
			*new++ = *(*line)++;
		free(line_orig);
	}
	while (**to_append)
	{
		if (**to_append != '\n')
			*new++ = *(*to_append)++;
		else
		{
			*new++ = *(*to_append)++;
			*new = '\0';
			*line = new_orig;
			return (1);
		}
	}
	*new = '\0';
	*line = new_orig;
	return (0);
}

size_t	null_safe_strlen(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (*str++)
		i++;
	return (i);
}

size_t	find_newline(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (*str)
	{
		if (*str == '\n')
			return (i + 1);
		str++;
		i++;
	}
	return (i);
}
