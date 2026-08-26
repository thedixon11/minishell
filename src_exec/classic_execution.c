/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   classic_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 20:39:27 by fducrot           #+#    #+#             */
/*   Updated: 2026/08/26 20:40:23 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

int	time_to_fork_and_exec(t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (error_int(data, I_FORK, strerror(errno), 1));
	if (pid == 0)
		child_process(data);
	if (data->current_cmd_nb == data->max_cmd_nb)
		data->last_pid = pid;
	ft_close_fd(&data->pipe_fd[1]);
	ft_close_fd(&data->old_read_fd);
	return (0);
}

int	time_to_pipe(t_data *data)
{
	if (data->max_cmd_nb > 0 && pipe(data->pipe_fd) == -1)
		return (error_int(data, I_PIPE, strerror(errno), 1));
	return (0);
}

void	classic_execution(t_data *data)
{
	if (data->current_cmd_nb < data->max_cmd_nb && time_to_pipe(data) == 1)
		return ;
	if (time_to_fork_and_exec(data) == 1)
		return ;
}
