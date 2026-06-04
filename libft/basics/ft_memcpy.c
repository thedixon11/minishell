/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/05 16:34:14 by jvasconc          #+#    #+#             */
/*   Updated: 2025/10/27 17:16:38 by jvasconc         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char	*ptr1;
	char	*ptr2;

	ptr1 = (char *) src;
	ptr2 = (char *) dest;
	if (!dest && !src)
		return (dest);
	while (n > 0)
	{
		*ptr2 = *ptr1;
		ptr1++;
		ptr2++;
		n--;
	}
	return (dest);
}
