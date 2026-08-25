/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no_command_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:12:39 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:12:40 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

void	no_command_process(t_data *data)
{
	if (data->current_cmd_nb < data->max_cmd_nb && time_to_pipe(data) == 1)
		return ;
	if (manage_redirections(data) == 1)
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
