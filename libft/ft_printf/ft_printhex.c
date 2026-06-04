/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printhex.c                                       :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:50:38 by jvasconc          #+#    #+#             */
/*   Updated: 2025/12/27 11:33:11 by jvasconc       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_printer(int *memory, int i)
{
	while (i >= 0)
	{
		write (1, &memory[i], 1);
		i--;
	}
}

int	ft_printhex(unsigned int arg, const char mod)
{
	int			memory[11];
	int			i;
	int			count;
	char		*base;

	if (mod == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	i = 0;
	count = 0;
	while ((arg / 16) != 0)
	{
		memory[i] = base[(arg % 16)];
		arg /= 16;
		i++;
	}
	count = i + 1;
	memory[i] = base[(arg % 16)];
	ft_printer(memory, i);
	return (count);
}
