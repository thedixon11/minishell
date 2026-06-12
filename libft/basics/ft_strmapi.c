/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 09:41:54 by jvasconc          #+#    #+#             */
/*   Updated: 2025/10/27 19:59:18 by jvasconc         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	size;
	char	*tab;

	size = ft_strlen(s);
	tab = ft_calloc(size + 1, sizeof(char));
	if (!tab)
		return (NULL);
	i = 0;
	while (s[i] != 0)
	{
		tab[i] = f(i, s[i]);
		i++;
	}
	return (tab);
}
