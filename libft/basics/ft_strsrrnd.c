/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsrrnd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/24 07:42:20 by jvasconc          #+#    #+#             */
/*   Updated: 2026/07/24 08:31:40 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strsrrnd(char *str, char *set)
{
	char	*temp;
	char	*result;

	temp = ft_strjoin(set, str);
	if (!temp)
		return (NULL);
	result = ft_strjoin(temp, set);
	ft_free((void **)&temp);
	if (!result)
		return (NULL);
	return (result);
}
