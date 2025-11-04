/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 22:40:08 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/03 16:25:09 by mlorenz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	find_newline(char *buf)
{
	size_t	i;

	i = 0;
	while (*buf)
	{
		if (*buf == '\n')
			return (i);
		i++;
	}
	return (0);
}