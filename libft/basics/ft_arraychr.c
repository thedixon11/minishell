/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_arraychr.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>     +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/02/17 13:24:45 by jvasconc       #+#    #+#                */
/*   Updated: 2026/02/17 14:11:59 by jvasconc       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_arraychr(char **tab, char c)
{
	size_t	x;
	size_t	y;
	size_t	count;

	y = 0;
	count = 0;
	if (!tab)
		return (-1);
	while (tab[y] != NULL)
	{
		x = 0;
		while (tab[y][x] != 0)
		{
			if (tab[y][x] == c)
				count++;
			x++;
		}
		y++;
	}
	return (count);
}
