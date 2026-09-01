/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   some_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:12:43 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:12:44 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"
#include <readline/readline.h>

int	dup2_process(t_data *data, int *fd1, int fd2)
{
	if (dup2(*fd1, fd2) == -1)
		return (error_int(data, I_DUP2, strerror(errno), 1));
	return (0);
}

t_line	*move_current_to_start(t_data *data)
{
	t_line	*current;

	current = data->line_cmd;
	while (current != NULL && current->cmd_nb != data->current_cmd_nb)
		current = current->next;
	return (current);
}

t_line	*move_current_to_cmd(t_data *data)
{
	t_line	*current;

	current = data->line_cmd;
	while (current != NULL && (current->type != T_COMMAND
			|| current->cmd_nb != data->current_cmd_nb))
		current = current->next;
	return (current);
}

void	free_and_close_life(t_data *data)
{
	close_line_cmd_fds(data);
	ft_close_fd(&data->saved_stdin);
	ft_close_fd(&data->saved_stdout);
	close_data_fds(data);
	free_cmd_args(data);
	ft_free((void **)&data->failed_content);
	if (data->do_i_exit == B_TRUE)
	{
		close_line_cmd_fds_full(data);
		free_line_cmd(&data->line_cmd);
		ft_free((void **)&data->cwd);
		ft_free((void **)&data->old_cwd);
		free_env(&data->env);
		ft_free((void **)&data);
		rl_clear_history();
	}
}
