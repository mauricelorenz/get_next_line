/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 13:37:57 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/08 18:47:49 by mlorenz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	create_or_grow_str(char **old_str, char *to_add, char to_add_end)
{
	char	*old_str_ptr;
	char	*new_str;
	char	*new_str_ptr;

	old_str_ptr = *old_str;
	new_str = malloc(len_to_char(*old_str, '\0')
			+ len_to_char(to_add, to_add_end) + 1);
	if (!new_str)
		return (1);
	new_str_ptr = new_str;
	if (*old_str)
	{
		while (*old_str_ptr)
			*new_str_ptr++ = *old_str_ptr++;
		free(*old_str);
	}
	*new_str_ptr = '\0';
	*old_str = new_str;
	return (0);
}

void	str_append(char **str, char **to_add, char to_add_end)
{
	size_t	i;
	size_t	len_to_add;
	char	*str_ptr;

	i = 0;
	len_to_add = len_to_char(*to_add, to_add_end);
	str_ptr = *str;
	while (*str_ptr)
		str_ptr++;
	while (i++ < len_to_add)
		*str_ptr++ = *(*to_add)++;
	*str_ptr = '\0';
}

int	new_rest(char **rest, char *buf_ptr)
{
	char	*rest_ptr;

	free (*rest);
	*rest = malloc(len_to_char(buf_ptr, '\0') + 1);
	if (!rest)
		return (1);
	rest_ptr = *rest;
	while (*buf_ptr)
		*rest_ptr++ = *buf_ptr++;
	*rest_ptr = '\0';
	return (0);
}

size_t	len_to_char(char *s, char c)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (*s)
	{
		if (*s == '\n' && c == '\n')
			return (i + 1);
		s++;
		i++;
	}
	return (i);
}
