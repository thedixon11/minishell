/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_squote.c                                   :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:53:25 by jvasconc          #+#    #+#             */
/*   Updated: 2026/03/17 09:07:52 by jvasconc       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_len(char const *s, char c, size_t start)
{
	size_t	end;
	size_t	quote_io;

	quote_io = 0;
	if (s[start] == '\'' )
	{
		quote_io = 1;
		start++;
	}
	end = start;
	while (s[end] != c && s[end] != 0 && quote_io == 0)
		end++;
	while (s[end] != 0 && quote_io == 1)
	{
		if (s[end] == '\'')
		{
			end += 2;
			return (end - start);
		}
		end++;
	}
	if (quote_io == 1)
		return (-1);
	return (end - start);
}

static int	go_to_next_c(char const *s, int i, char c)
{
	size_t	squote_io;

	squote_io = 0;
	while (s[i] != 0)
	{
		if (s[i] == '\'' && squote_io == 0)
		{
			squote_io = 1;
			i++;
		}
		if (s[i] == '\'' && squote_io == 1)
		{
			i++;
			return (i);
		}
		else if (s[i] == c && squote_io == 0)
			return (i);
		if (s[i] != 0)
			i++;
	}
	if (squote_io == 1)
		return (-1);
	return (i);
}

static char	**xtab(char const *s, char c, char **tab)
{
	size_t	y;
	size_t	start;
	char	*temp;

	y = 0;
	start = 0;
	while (s[start] != 0)
	{
		while (s[start] == c)
			start++;
		if (s[start] != c && s[start] != 0)
		{
			temp = ft_substr(s, start, ft_len(s, c, start));
			if (!temp)
				return (ft_free_tab(&tab), NULL);
			tab[y] = ft_strtrim(temp, "'");
			free(temp);
			y++;
			start += ft_len(s, c, start);
		}
	}
	return (tab);
}

static char	**ytab(char const *s, char c)
{
	int		i;
	int		j;
	size_t	ylen;
	char	**tab;

	i = 0;
	j = 0;
	ylen = 0;
	while (s[i] != 0)
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != 0)
			ylen++;
		j = go_to_next_c(s, i, c);
		i = j;
		if (i == -1)
			return (NULL);
	}
	tab = ft_calloc(ylen + 1, sizeof(char *));
	if (!tab)
		return (NULL);
	return (tab);
}

char	**ft_split_squote(char const *s, char c)
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
