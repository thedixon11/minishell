/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   ft_strrm.c                                          :+:    :+:           */
/*                                                      +:+                   */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>     +#+                    */
/*                                                    +#+                     */
/*   Created: 2026/03/02 16:56:32 by jvasconc       #+#    #+#                */
/*   Updated: 2026/03/02 18:05:09 by jvasconc       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrm(const char *s, size_t len)
{
	size_t	i;
	size_t	size;
	char	*new_str;

	i = 0;
	size = 0;
	size = ft_strlen(s + len);
	new_str = ft_calloc(size + 1, sizeof(char));
	if (new_str == NULL)
		return (NULL);
	while (s[len + 1] != 0)
	{
		new_str[i] = s[len + 1];
		i++;
		len++;
	}
	return (new_str);
}
