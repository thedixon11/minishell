/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printstring.c                                    :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:25:36 by jvasconc          #+#    #+#             */
/*   Updated: 2025/12/27 11:33:21 by jvasconc       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printstring(char *arg)
{
	size_t	i;

	i = 0;
	if (arg == NULL)
		return (write(1, "(null)", 6));
	while (arg[i] != 0)
	{
		write(1, &arg[i], 1);
		i++;
	}
	return (i);
}
