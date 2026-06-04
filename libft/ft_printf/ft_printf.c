/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                         :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 17:13:46 by jvasconc          #+#    #+#             */
/*   Updated: 2025/12/27 11:33:07 by jvasconc       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_run(const char *str, va_list ap, size_t count)
{
	size_t	i;

	i = 0;
	while (str[i] != 0)
	{
		while (str[i] != '%' && str[i] != 0)
		{
			write(1, &str[i], 1);
			count++;
			i++;
		}
		if (str[i] == '%' && str[i] != 0)
			i++;
		if (str[i] != 0)
			count += ft_conv(str[i], ap);
		if (str[i] != 0)
			i++;
	}
	return (count);
}

int	ft_printf(const char *str, ...)
{
	size_t	i;
	va_list	ap;
	int		count;

	i = 0;
	count = 0;
	if (!str)
		return (-1);
	va_start(ap, str);
	count = ft_run(str, ap, count);
	va_end(ap);
	return (count);
}
