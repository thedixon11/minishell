/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                     :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 08:41:02 by jvasconc          #+#    #+#             */
/*   Updated: 2026/03/14 09:01:25 by jvasconc       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*extract_line_gnl(char *stash)
{
	size_t	i;
	char	*line;

	i = 0;
	if (!stash)
		return (NULL);
	if (has_new_line_gnl(stash) == 1)
	{
		while (stash[i] != '\n')
			i++;
	}
	while (stash[i] != 0 && stash[i] != '\n')
		i++;
	i++;
	line = ft_calloc_gnl((i + 1), sizeof(char));
	if (!line)
		return (free(line), line = NULL, NULL);
	i = 0;
	while (stash[i] != 0 && stash[i] != '\n')
	{
		line[i] = stash[i];
		i++;
	}
	line[i] = stash[i];
	return (line);
}

char	*update_stash_gnl(char *stash)
{
	char	*newstash;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!stash)
		return (NULL);
	while (stash[i] != '\n' && stash[i] != 0)
		i++;
	if (stash[i] == '\n')
		i++;
	while (stash[i + j] != 0)
		j++;
	newstash = ft_calloc_gnl((j + 1), sizeof(char));
	if (!newstash)
		return (free(newstash), newstash = NULL,
			free(stash), stash = NULL, NULL);
	j = 0;
	while (stash[i + j] != 0)
	{
		newstash[j] = stash[i + j];
		j++;
	}
	return (free(stash), stash = NULL, newstash);
}

char	*read_file_gnl(int fd, char **stash)
{
	ssize_t	nb_bytes_read;
	char	*buffer;
	char	*temp;

	if (!stash[fd])
		stash[fd] = ft_strdup_gnl("");
	buffer = ft_calloc_gnl((BUFFER_SIZE + 1), sizeof(char));
	if (!buffer)
		return (free(buffer), buffer = NULL, NULL);
	buffer[BUFFER_SIZE] = '\0';
	nb_bytes_read = 1;
	while (has_new_line_gnl(buffer) == 0 && nb_bytes_read > 0)
	{
		nb_bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (nb_bytes_read < 0)
			return (free(buffer), buffer = NULL,
				free(stash[fd]), stash[fd] = NULL, NULL);
		buffer[nb_bytes_read] = '\0';
		temp = stash[fd];
		stash[fd] = ft_strjoin_gnl(temp, buffer);
		free (temp);
	}
	return (free(buffer), buffer = NULL, stash[fd]);
}

char	*get_next_line(int fd, const char *limiter, int len_of_limiter)
{
	char		*line;
	static char	*stash[1024];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	if (has_new_line_gnl(stash[fd]) == 0)
		stash[fd] = read_file_gnl(fd, stash);
	if (stash[fd] == NULL)
		return (NULL);
	line = extract_line_gnl(stash[fd]);
	if (line == NULL)
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	stash[fd] = update_stash_gnl(stash[fd]);
	if (stash[fd] == NULL)
		return (NULL);
	if (stash[fd][0] == 0 && line[0] == 0)
		return (free(line), line = NULL,
			free(stash[fd]), stash[fd] = NULL, NULL);
	else if (ft_strncmp(line, limiter, len_of_limiter) == 0)
		return (free(stash[fd]), stash[fd] = NULL, line);
	else
		return (line);
}
