/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:10:11 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:10:13 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

int	ft_pwd(t_data *data)
{
	char	*cwd_to_print;

	cwd_to_print = getcwd(NULL, 0);
	if (!cwd_to_print)
		return (error_int(data, I_PWD, strerror(errno), 1));
	if (ft_printf("%s\n", cwd_to_print) == -1)
		return (ft_free((void **)&cwd_to_print), 1);
	ft_free((void **)&cwd_to_print);
	return (0);
}
