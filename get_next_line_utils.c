/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:00:27 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/18 15:58:32 by mlorenz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_and_null(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*char_dest;
	char	*char_src;

	i = 0;
	char_dest = (char *)dest;
	char_src = (char *)src;
	if (!dest && !src)
		return (0);
	while (i++ < n)
		*char_dest++ = *char_src++;
	return (dest);
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
