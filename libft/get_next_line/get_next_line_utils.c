/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   get_next_line_utils_bonus.c                         :+:    :+:           */
/*                                                      +:+                   */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>     +#+                    */
/*                                                    +#+                     */
/*   Created: 2025/11/14 10:21:57 by jvasconc       #+#    #+#                */
/*   Updated: 2025/12/27 16:26:04 by jvasconc       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

size_t	has_new_line_gnl(char *str)
{
	size_t	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len] != 0)
	{
		if (str[len] == '\n')
			return (1);
		len++;
	}
	return (0);
}

char	*ft_calloc_gnl(size_t nmemb, size_t size)
{
	char	*tab;
	size_t	i;

	i = 0;
	if (nmemb * size == 0)
		return (malloc(1));
	if (nmemb > SIZE_MAX / size)
		return (NULL);
	tab = malloc(nmemb * sizeof(char));
	if (!tab)
		return (free(tab), tab = NULL, NULL);
	while (i < nmemb)
	{
		tab[i] = 0;
		i++;
	}
	return (tab);
}

size_t	ft_strlen_gnl(char *s)
{
	size_t	size;

	size = 0;
	if (!s)
		return (0);
	while (s[size] != 0)
		size++;
	return (size);
}

char	*ft_strjoin_gnl(char *temp, char *buffer)
{
	char	*tab;
	size_t	len;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!temp || !buffer)
		return (free(buffer), buffer = NULL, free(temp),
			temp = NULL, NULL);
	len = ft_strlen_gnl(temp) + ft_strlen_gnl(buffer);
	tab = ft_calloc_gnl((len + 1), sizeof(char));
	if (!tab)
		return (free(tab), tab = NULL, NULL);
	while (temp != NULL && temp[i] != 0)
	{
		tab[i] = temp[i];
		i++;
	}
	while (buffer[j] != 0)
	{
		tab[i + j] = buffer[j];
		j++;
	}
	return (tab);
}

char	*ft_strdup_gnl(char *stash)
{
	char	*tab;
	size_t	len;
	size_t	i;

	i = 0;
	len = ft_strlen_gnl(stash);
	tab = ft_calloc_gnl((len + 1), sizeof(char));
	if (!tab)
		return (free(tab), tab = NULL, NULL);
	while (stash[i] != 0)
	{
		tab[i] = stash[i];
		i++;
	}
	return (tab);
}
