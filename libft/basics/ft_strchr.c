/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 08:48:10 by jvasconc          #+#    #+#             */
/*   Updated: 2025/10/27 17:40:25 by jvasconc         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*ptr;
	size_t		i;

	i = 0;
	ptr = s;
	while (ptr[i] != 0)
	{
		if (ptr[i] == (unsigned char) c)
			return ((char *)(s + i));
		i++;
	}
	if ((unsigned char) c == 0)
		return ((char *)(s + i));
	return (0);
}
