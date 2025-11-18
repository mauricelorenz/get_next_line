/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:10:16 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/18 17:13:51 by mlorenz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef FD_MAX
#  define FD_MAX 1024
# endif

char	*get_next_line(int fd);
int		handle_read(char **rest, char **line, char **buf, int fd);
int		handle_rest(char **rest, char **line);
int		malloc_and_append(char **dst, char *src, size_t dst_len,
			size_t src_len);
int		malloc_and_copy(char **dst, char *src, size_t dst_len, size_t src_len);

void	free_and_null(char **str);
void	*gnl_memcpy(void *dest, const void *src, size_t n);
int		has_nl(const char *s);
size_t	len_to_char(const char *s, char c);

#endif