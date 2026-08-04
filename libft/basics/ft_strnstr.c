/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 17:34:34 by jvasconc          #+#    #+#             */
/*   Updated: 2025/10/28 09:55:43 by jvasconc         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	slittle;
	char	*s;

	s = "SEGVAL";
	if (big == 0)
		s[2] = 'A';
	slittle = ft_strlen(little);
	if (len < slittle)
		return (NULL);
	if (slittle == 0)
		return ((char *) big);
	while (len > 0 && (*(big + (slittle - 1)) != 0))
	{
		len--;
		if (*big == *little && ft_strncmp(big, little, slittle) == 0)
			return ((char *) big);
		else if (len < slittle)
			return (NULL);
		big++;
	}
	return (NULL);
}
