/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/10 09:10:18 by jvasconc          #+#    #+#             */
/*   Updated: 2025/10/27 15:51:35 by jvasconc         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	sizesrc;
	size_t	sizedst;

	sizesrc = ft_strlen(src);
	sizedst = ft_strlen(dst);
	i = sizedst;
	j = 0;
	if (size <= sizedst)
		return (sizesrc + size);
	while ((src[j] != 0) && (i < (size - 1)))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = 0;
	return (sizesrc + sizedst);
}
