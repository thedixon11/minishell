/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                         :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 20:33:43 by jvasconc          #+#    #+#             */
/*   Updated: 2025/12/27 15:13:04 by jvasconc       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "../libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <stdarg.h>

int	ft_printf(const char *str, ...);
int	ft_conv(const char mod, va_list ap);
int	ft_printmodulo(void);
int	ft_printchar(int arg);
int	ft_printdigit(int arg);
int	ft_printhex(unsigned int arg, const char mod);
int	ft_printpointer(void *arg);
int	ft_printstring(char *arg);
int	ft_printuint(unsigned int arg);

#endif
