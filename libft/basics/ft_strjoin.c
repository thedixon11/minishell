/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                        :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 17:38:17 by jvasconc          #+#    #+#             */
/*   Updated: 2026/02/13 17:22:58 by jvasconc       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len;
	char	*tab;
	size_t	sizes1;

	sizes1 = ft_strlen(s1) + 1;
	len = sizes1 + ft_strlen(s2);
	tab = ft_calloc(len, sizeof(char));
	if (!tab)
		return (0);
	ft_strlcpy(tab, s1, sizes1);
	ft_strlcat(tab, s2, len);
	return (tab);
}
