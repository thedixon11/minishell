/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_conv.c                                           :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:29:48 by jvasconc          #+#    #+#             */
/*   Updated: 2025/12/27 11:32:40 by jvasconc       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_conv(const char mod, va_list ap)
{
	if (mod == 'c')
		return (ft_printchar(va_arg(ap, int)));
	else if (mod == 'd' || mod == 'i')
		return (ft_printdigit(va_arg(ap, int)));
	else if (mod == 's')
		return (ft_printstring(va_arg(ap, char *)));
	else if (mod == '%')
		return (ft_printmodulo());
	else if (mod == 'X' || mod == 'x')
		return (ft_printhex(va_arg(ap, unsigned int), mod));
	else if (mod == 'u')
		return (ft_printuint(va_arg(ap, unsigned int)));
	else if (mod == 'p')
		return (ft_printpointer(va_arg(ap, void *)));
	else
		return (0);
}
