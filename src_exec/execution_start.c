/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_start.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 19:55:20 by fducrot           #+#    #+#             */
/*   Updated: 2026/08/26 19:55:20 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

void	set_fd_pipe_zero(t_data *data)
{
	t_line	*current;

	current = data->line_cmd;
	while (current != NULL)
	{
		if (current->type == T_PIPE_IN || current->type == T_PIPE_OUT)
		{
			current->fd = 0;
			current->fd_of_pipe = NULL;
		}
		current = current->next;
	}
}

int	store_stdin_stdout(t_data *data)
{
	data->saved_stdin = dup(STDIN_FILENO);
	if (data->saved_stdin == -1)
		return (error_int(data, I_DUP, strerror(errno), 1));
	data->saved_stdout = dup(STDOUT_FILENO);
	if (data->saved_stdout == -1)
		return (error_int(data, I_DUP, strerror(errno), 1));
	return (0);
}

void	data_creation(t_data *data)
{
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->old_read_fd = -1;
	data->current_cmd_nb = 0;
	data->last_pid = 0;
}

void	execution_start(t_data *data)
{
	int	error;

	data_creation(data);
	set_fd_pipe_zero(data);
	data->do_i_exit = B_FALSE;
	error = store_stdin_stdout(data);
	if (error == 0)
		error = val_manager(data);
	if (error == 0)
		error = heredoc_exec(data);
	init_signal_prompt();
	if (error == 0)
		execute_cmds(data);
	free_and_close_life(data);
	init_signal_prompt();
}
