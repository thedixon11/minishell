/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:09:20 by jvasconc          #+#    #+#             */
/*   Updated: 2025/10/27 19:57:18 by jvasconc         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*tab;
	size_t	len;

	len = ft_strlen(s) + 1;
	tab = ft_calloc(len, sizeof(char));
	if (!tab)
		return (NULL);
	ft_strlcpy(tab, s, len);
	return (tab);
}
