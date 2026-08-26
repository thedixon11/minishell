/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_command_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 19:53:48 by fducrot           #+#    #+#             */
/*   Updated: 2026/08/26 19:53:58 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

void	no_command_process(t_data *data)
{
	if (data->current_cmd_nb < data->max_cmd_nb && time_to_pipe(data) == 1)
		return ;
	if (open_fd_in_line_cmd(data) == 1)
		return ;
}

t_bool	is_there_command(t_data *data)
{
	t_line	*current;

	current = move_current_to_start(data);
	while (current != NULL && current->cmd_nb == data->current_cmd_nb)
	{
		if (current->type == T_COMMAND)
			return (B_TRUE);
		current = current->next;
	}
	return (B_FALSE);
}
