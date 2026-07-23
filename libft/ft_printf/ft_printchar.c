/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printchar.c                                      :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:29:05 by jvasconc          #+#    #+#             */
/*   Updated: 2025/12/27 11:32:56 by jvasconc       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_printchar(int arg)
{
	int	print;

	print = arg;
	write(1, &print, 1);
	return (1);
}
