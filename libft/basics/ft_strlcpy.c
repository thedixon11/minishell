/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/09 08:39:11 by jvasconc          #+#    #+#             */
/*   Updated: 2025/10/27 17:41:07 by jvasconc         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	sizesrc;

	i = 0;
	sizesrc = ft_strlen(src);
	if (size == 0)
		return (sizesrc);
	while (src[i] != 0 && i < (size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = 0;
	return (sizesrc);
}
