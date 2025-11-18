/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:00:14 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/18 15:56:01 by mlorenz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
int		handle_read(char **rest, char **line, char **buf, int fd);
int		handle_rest(char **rest, char **line);
int		malloc_and_append(char **dst, char *src, size_t dst_len,
			size_t src_len);
int		malloc_and_copy(char **dst, char *src, size_t dst_len, size_t src_len);

char	*free_and_null(char **str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
int		has_nl(const char *s);
size_t	len_to_char(const char *s, char c);

#endif