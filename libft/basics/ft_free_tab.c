/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_free_tab.c                                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>     +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/03/05 09:01:02 by jvasconc       #+#    #+#                */
/*   Updated: 2026/03/16 11:48:46 by jvasconc       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_tab(char ***tab)
{
	size_t	y;

	y = 0;
	while (*tab[y] != NULL)
	{
		free(*tab[y]);
		y++;
	}
	free(*tab);
	*tab = NULL;
}
