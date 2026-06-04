/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                          :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:53:25 by jvasconc          #+#    #+#             */
/*   Updated: 2026/03/16 14:10:05 by jvasconc       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(char const *s, char c, size_t start)
{
	size_t	end;

	end = start;
	while (s[end] != c && s[end] != 0)
		end++;
	return (end - start);
}

static void	*ft_free(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i] != 0)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static char	**xtab(char const *s, char c, char **tab)
{
	size_t	y;
	size_t	start;

	y = 0;
	start = 0;
	while (s[start] != 0)
	{
		while (s[start] == c)
			start++;
		if (s[start] != c && s[start] != 0)
		{
			tab[y] = ft_substr(s, start, ft_len(s, c, start));
			if (!tab[y])
				return (ft_free(tab));
			y++;
			start += ft_len(s, c, start);
		}
	}
	return (tab);
}

static char	**ytab(char const *s, char c)
{
	size_t	i;
	size_t	ylen;
	char	**tab;

	i = 0;
	ylen = 0;
	while (s[i] != 0)
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != 0)
			ylen++;
		while (s[i] != c && s[i] != 0)
			i++;
	}
	tab = ft_calloc(ylen + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (ft_strlen(s) == 0)
	{
		tab = ft_calloc(1, sizeof(char *));
		if (tab == 0)
			return (NULL);
		tab[0] = NULL;
		return (tab);
	}
	tab = ytab(s, c);
	if (tab == NULL)
		return (NULL);
	tab = xtab(s, c, tab);
	return (tab);
}
