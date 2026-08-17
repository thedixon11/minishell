/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_quote.c                                   :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:53:25 by jvasconc          #+#    #+#             */
/*   Updated: 2026/03/17 09:07:52 by jvasconc       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	go_to_next_c(char const *s, int *i, char c)
{
	char	quote;

	quote = 'a';
	while (s[*i] != 0 && s[*i] != c)
	{
		if (s[*i] == '\'' || s[*i] == '\"')
		{
			quote = s[*i];
			(*i)++;
			while (s[*i] != quote)
			{
				if (s[*i] == 0)
				{
					*i = -1;
					return ;
				}
				(*i)++;
			}
		}
		(*i)++;
	}
}

static size_t	ft_len(char const *s, char c, size_t start)
{
	int	end;

	end = start;
	go_to_next_c(s, &end, c);
	return (end - start);
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
				return (ft_free_tab(&tab), NULL);
			y++;
			start += ft_len(s, c, start);
		}
	}
	return (tab);
}

static char	**ytab(char const *s, char c)
{
	int		i;
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
		go_to_next_c(s, &i, c);
		if (i == -1)
			return (NULL);
	}
	tab = ft_calloc(ylen + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	return (tab);
}

char	**ft_split_quote(char const *s, char c)
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
