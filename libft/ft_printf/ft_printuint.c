/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printuint.c                                      :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:48:39 by jvasconc          #+#    #+#             */
/*   Updated: 2025/12/27 11:33:22 by jvasconc       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printuint(unsigned int arg)
{
	int			memory[11];
	int			i;
	long int	nbl;
	int			count;

	nbl = arg;
	i = 0;
	count = 0;
	while ((nbl / 10) != 0)
	{
		memory[i] = (nbl % 10) + 48;
		nbl /= 10;
		i++;
	}
	count = i + 1;
	memory[i] = (nbl % 10) + 48;
	while (i >= 0)
	{
		write (1, &memory[i], 1);
		i--;
	}
	return (count);
}
