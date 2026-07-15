/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                        :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 11:06:34 by jvasconc          #+#    #+#             */
/*   Updated: 2026/03/16 14:58:33 by jvasconc       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	findend(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(s1) - 1;
	j = 0;
	while (set[j] != 0)
	{
		if (s1[i] == set[j])
		{
			i--;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

static size_t	findstart(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (set[j] != 0)
	{
		if (s1[i] == set[j])
		{
			i++;
			j = 0;
		}
		else
			j++;
	}
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	start;
	size_t	end;
	size_t	len;

	if (s1[0] == 0)
		return (ft_strdup(""));
	if (!s1)
		return (NULL);
	start = findstart(s1, set);
	end = findend(s1, set);
	len = end - start + 1;
	trim = ft_substr(s1, start, len);
	if (!trim)
		return (NULL);
	return (trim);
}
