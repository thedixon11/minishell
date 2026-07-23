/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_free.c                                           :+:    :+:           */
/*                                                      +:+                   */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>     +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/07/10 11:35:17 by jvasconc       #+#    #+#                */
/*   Updated: 2026/07/10 11:35:29 by jvasconc       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free(void **ptr)
{
	if (*ptr != NULL)
	{
		free(*ptr);
		*ptr = NULL;
	}
}
