/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printpointer.c                                   :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 19:44:18 by jvasconc          #+#    #+#             */
/*   Updated: 2025/12/27 11:33:18 by jvasconc       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static void	ft_printer(unsigned long long *memory, int i)
{
	while (i >= 0)
	{
		write (1, &memory[i], 1);
		i--;
	}
}

int	ft_printpointer(void *arg)
{
	unsigned long long	adr;
	unsigned long long	memory[14];
	int					i;
	int					count;
	char				*base;

	if (arg == NULL)
		return (write(1, "(nil)", 5));
	adr = (unsigned long long) arg;
	base = "0123456789abcdef";
	write(1, "0x", 2);
	i = 0;
	count = 2;
	while (adr >= 16)
	{
		memory[i] = base[(adr % 16)];
		adr /= 16;
		i++;
	}
	count += (i + 1);
	memory[i] = base[(adr % 16)];
	ft_printer(memory, i);
	return (count);
}
