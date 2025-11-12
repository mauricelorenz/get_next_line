/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 16:05:11 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/12 17:31:10 by mlorenz          ###   ########.fr       */
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
int		rest_to_line(char **line, char **rest, char **rest_orig);
int		read_to_line(char **line, char **buf, int fd);
int		buf_to_line(char **line, char *buf);
int		buf_to_rest(char **buf, char **rest);
size_t	gnl_strlen(char *s);
size_t	gnl_nllen(char *s);

#endif