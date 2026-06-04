/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 16:21:33 by jvasconc          #+#    #+#             */
/*   Updated: 2025/10/27 17:38:57 by jvasconc         ###   ####lausanne.ch   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	int			memory[11];
	int			i;
	long int	nbl;

	nbl = n;
	i = 0;
	if (nbl < 0)
	{
		write(fd, "-", 1);
		nbl *= (-1);
	}
	while ((nbl / 10) != 0)
	{
		memory[i] = (nbl % 10) + 48;
		nbl /= 10;
		i++;
	}
	memory[i] = (nbl % 10) + 48;
	while (i >= 0)
	{
		write (fd, &memory[i], 1);
		i--;
	}
}
