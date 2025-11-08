/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlorenz <mlorenz@student.42heilbronn.de    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 13:38:06 by mlorenz           #+#    #+#             */
/*   Updated: 2025/11/08 18:30:35 by mlorenz          ###   ########.fr       */
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
int		create_or_grow_str(char **old_str, char *to_add, char to_add_end);
void	str_append(char **str, char **to_add, char to_add_end);
int		new_rest(char **rest, char *buf_ptr);
size_t	len_to_char(char *s, char c);

#endif