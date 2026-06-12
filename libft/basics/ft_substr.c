/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 16:44:55 by jvasconc          #+#    #+#             */
/*   Updated: 2025/10/30 10:22:37 by jvasconc         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*tab;
	size_t	size;

	size = 0;
	if (!s)
		return (NULL);
	else if (start > ft_strlen(s))
		return (ft_strdup(""));
	else if (len > ft_strlen(s + start))
		size = ft_strlen(s + start);
	else
		size = len;
	tab = ft_calloc(size + 1, sizeof(char));
	if (!tab)
		return (NULL);
	ft_strlcpy(tab, s + start, size + 1);
	return (tab);
}
