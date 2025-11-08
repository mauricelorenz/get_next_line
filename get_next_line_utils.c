/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 13:37:57 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/08 14:55:31 by mlorenz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	create_or_grow_str(char **old_str, char *to_add)
{
	char	*old_str_orig;
	char	*new_str;
	char	*new_str_orig;

	old_str_orig = *old_str;
	new_str = malloc(len_to_char(*old_str, '\0')
			+ len_to_char(to_add, '\n') + 1);
	if (!new_str)
		return (1);
	new_str_orig = new_str;
	if (*old_str)
	{
		while (**old_str)
			*new_str++ = *(*old_str)++;
		free(old_str_orig);
	}
	*new_str = '\0';
	*old_str = new_str_orig;
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
