/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_arraydup.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>     +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/02/17 09:43:02 by jvasconc       #+#    #+#                */
/*   Updated: 2026/02/24 13:41:07 by jvasconc       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**dup_y_axis(char **tab)
{
	size_t	y;
	char	**dup;

	y = 0;
	while (tab[y] != NULL)
		y++;
	dup = ft_calloc(y + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	return (dup);
}

char	**ft_arraydup(char **tab)
{
	size_t	y;
	char	**dup;

	y = 0;
	if (!tab)
		return (NULL);
	dup = dup_y_axis(tab);
	if (!dup)
		return (NULL);
	while (tab[y] != NULL)
	{
		dup[y] = ft_strdup(tab[y]);
		y++;
	}
	return (dup);
}
