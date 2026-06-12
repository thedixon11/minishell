/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                     :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 15:54:08 by jvasconc          #+#    #+#             */
/*   Updated: 2026/03/16 10:23:03 by jvasconc       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>

void	ft_putendl_fd(char *s, int fd)
{
	size_t	i;
	char	*temp;

	if (!s)
		return ;
	i = ft_strlen(s);
	temp = ft_strjoin(s, "\n");
	write(fd, temp, i + 1);
	free(temp);
}
