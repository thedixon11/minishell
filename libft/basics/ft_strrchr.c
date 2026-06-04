/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 09:22:30 by jvasconc          #+#    #+#             */
/*   Updated: 2025/10/27 17:15:55 by jvasconc         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t	last;

	last = ft_strlen(s);
	if ((unsigned char) c == 0)
		return ((char *)s + last);
	while (last != 0)
	{
		if (s[last] == (unsigned char) c)
			return ((char *)&s[last]);
		last--;
	}
	if (s[last] == (unsigned char) c)
		return ((char *)&s[last]);
	return (NULL);
}
