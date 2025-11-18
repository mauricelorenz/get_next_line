/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:10:25 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/18 18:39:13 by mlorenz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_and_null(char **str)
{
	free(*str);
	*str = NULL;
}

void	*gnl_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*char_dst;
	char	*char_src;

	i = 0;
	char_dst = (char *)dst;
	char_src = (char *)src;
	if (!dst && !src)
		return (NULL);
	while (i++ < n)
		*char_dst++ = *char_src++;
	return (dst);
}

int	has_nl(const char *s)
{
	while (*s)
	{
		if ((unsigned char)*s == '\n')
			return (1);
		s++;
	}
	return (0);
}

size_t	len_to_char(const char *s, char c)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (*s)
	{
		if (*s++ == '\n' && c == '\n')
			return (i + 1);
		i++;
	}
	return (i);
}
