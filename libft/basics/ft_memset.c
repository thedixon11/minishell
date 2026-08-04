/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:25:12 by jvasconc          #+#    #+#             */
/*   Updated: 2025/10/27 17:43:24 by jvasconc         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;
	char	*ptr;

	ptr = (char *) s;
	i = 0;
	while (i < n)
	{
		*ptr = (char) c;
		i++;
		ptr++;
	}
	return (s);
}
