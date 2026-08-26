/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:09:29 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:09:31 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

int	echo_no_args(t_data *data)
{
	if (write(STDOUT_FILENO, "\n", 1) == -1)
		return (error_int(data, I_WRITE, strerror(errno), 1));
	if (data->do_i_exit == B_TRUE)
	{
		free_env(&data->env);
		free_and_close_life(data);
		exit(0);
	}
	return (0);
}

t_bool	skip_option_n(char **args_cmd, int *y)
{
	int	x;

	x = 2;
	if (args_cmd[*y][0] != '-' || args_cmd[*y][1] != 'n')
		return (B_TRUE);
	while (args_cmd[*y][x] != 0 && args_cmd[*y][x] == 'n')
		x++;
	if (args_cmd[*y][x] != 0)
		return (B_TRUE);
	(*y)++;
	while (args_cmd[*y] != NULL)
	{
		x = 2;
		if (args_cmd[*y][0] != '-' || args_cmd[*y][1] != 'n')
			return (B_FALSE);
		while (args_cmd[*y][x] != 0 && args_cmd[*y][x] == 'n')
			x++;
		if (args_cmd[*y][x] != 0)
			return (B_FALSE);
		(*y)++;
	}
	return (B_FALSE);
}

int	between_args(t_data *data, char **args_cmd, int y, t_bool do_i_return)
{
	if (args_cmd[y + 1] == NULL && do_i_return == B_TRUE)
	{
		if (write(STDOUT_FILENO, "\n", 1) == -1)
			return (error_int(data, I_ECHO, strerror(errno), 1));
	}
	if (args_cmd[y + 1] != NULL)
	{
		if (write(STDOUT_FILENO, " ", 1) == -1)
			return (error_int(data, I_ECHO, strerror(errno), 1));
	}
	return (0);
}

int	ft_echo(t_data *data, char **args_cmd)
{
	int		y;
	int		len;
	t_bool	do_i_return;

	y = 1;
	len = 0;
	if (args_cmd[1] == NULL)
		return (echo_no_args(data));
	do_i_return = skip_option_n(args_cmd, &y);
	while (args_cmd[y] != NULL)
	{
		len = ft_strlen(args_cmd[y]);
		if (write(STDOUT_FILENO, args_cmd[y], len) == -1)
			return (error_int(data, I_ECHO, strerror(errno), 1));
		if (between_args(data, args_cmd, y, do_i_return) == 1)
			return (1);
		y++;
	}
	return (0);
}
