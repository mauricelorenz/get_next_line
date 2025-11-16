/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/13 13:00:14 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/16 21:19:35 by mlorenz          ###   ########.fr       */
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
char	*malloc_and_append(char **dst, char *src, size_t dst_len, size_t src_len);
char	*malloc_and_copy(char **dst, char *src, size_t dst_len, size_t src_len);

char	*free_and_null(char **str);
void	*ft_memcpy(void *dest, const void *src, size_t n);
char	*ft_strchr(const char *s, int c);
size_t	null_safe_nllen(const char *s);
size_t	null_safe_strlen(const char *s);

#endif