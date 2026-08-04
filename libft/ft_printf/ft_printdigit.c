/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printdigit.c                                     :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:26:43 by jvasconc          #+#    #+#             */
/*   Updated: 2025/12/27 11:33:04 by jvasconc       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_printer(int i, int *memory)
{
	while (i >= 0)
	{
		write(1, &memory[i], 1);
		i--;
	}
}

int	ft_printdigit(int arg)
{
	int			memory[11];
	int			i;
	long int	nbl;
	int			count;

	nbl = arg;
	i = 0;
	count = 0;
	if (nbl < 0)
	{
		write(1, "-", 1);
		nbl *= (-1);
		count++;
	}
	while ((nbl / 10) != 0)
	{
		memory[i] = (nbl % 10) + 48;
		nbl /= 10;
		i++;
	}
	count += i + 1;
	memory[i] = (nbl % 10) + 48;
	ft_printer(i, memory);
	return (count);
}
