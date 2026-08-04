/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                     :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 08:53:47 by jvasconc          #+#    #+#             */
/*   Updated: 2026/03/14 09:02:23 by jvasconc       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include "../libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*ft_next_line_gnl(int fd);
char	*ft_strjoin_gnl(char *temp, char *buffer);
char	*ft_strdup_gnl(char *stash);
size_t	ft_strlen_gnl(char *s);
char	*extract_line_gnl(char *stash);
char	*update_stash_gnl(char *temp);
char	*read_file_gnl(int fd, char **stash);
size_t	has_new_line_gnl(char *str);
char	*ft_calloc_gnl(size_t nmemb, size_t size);
char	*get_next_line(int fd, const char *limiter, int len_of_limiter);

#endif
