/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redirections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:12:29 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:12:33 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

int	patch_others_redir(t_data *data)
{
	t_line	*current;
	int		error;

	error = 0;
	current = data->line_cmd;
	while (current != NULL && current->cmd_nb != data->current_cmd_nb)
		current = current->next;
	while (current != NULL && error != 1
		&& current->cmd_nb == data->current_cmd_nb)
	{
		if (error != 1 && (current->type == T_INPUT
				|| current->type == T_HEREDOC))
			error = dup2_process(data, &current->fd, STDIN_FILENO);
		else if (data->error != 1 && (current->type == T_OUTPUT_APPEND
				|| current->type == T_OUTPUT_TRUNC))
			error = dup2_process(data, &current->fd, STDOUT_FILENO);
		current = current->next;
	}
	if (error == 1)
		return (1);
	return (0);
}

int	first_patch_pipes_redir(t_data *data)
{
	t_line	*current;
	int		error;

	current = data->line_cmd;
	error = 0;
	while (current != NULL && current->cmd_nb != data->current_cmd_nb)
		current = current->next;
	while (current != NULL && error != 1
		&& current->cmd_nb == data->current_cmd_nb)
	{
		if (error != 1 && current->type == T_PIPE_IN)
			error = dup2_process(data, current->fd_of_pipe, STDIN_FILENO);
		else if (error != 1 && current->type == T_PIPE_OUT)
			error = dup2_process(data, current->fd_of_pipe, STDOUT_FILENO);
		current = current->next;
	}
	if (error == 1)
		return (1);
	return (0);
}

int	open_fd_in_line_cmd(t_data *data)
{
	t_line	*current;

	current = move_current_to_start(data);
	while (current != NULL && current->cmd_nb == data->current_cmd_nb)
	{
		if (check_ambiguous_redir(data, current) == 1)
			return (1);
		if (current->type == T_PIPE_IN)
			current->fd_of_pipe = &data->old_read_fd;
		else if (current->type == T_INPUT)
			current->fd = open(current->content_xpand[0], O_RDONLY);
		else if (current->type == T_OUTPUT_APPEND)
			current->fd = open(current->content_xpand[0],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (current->type == T_OUTPUT_TRUNC)
			current->fd = open(current->content_xpand[0],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (current->type == T_PIPE_OUT)
			current->fd_of_pipe = &data->pipe_fd[1];
		if (current->fd < 0 && current->type != T_COMMAND)
			return (error_int(data, current->content_xpand[0], strerror(errno),
					1));
		current = current->next;
	}
	return (0);
}

int	check_ambiguous_redir(t_data *data, t_line *current)
{
	int	y;

	y = 0;
	if (current->type == T_INPUT || current->type == T_OUTPUT_APPEND
		|| current->type == T_OUTPUT_TRUNC)
	{
		if (current->content_xpand == NULL || current->content_xpand[0] == 0)
			return (error_int(data, current->content, AMB_REDIR_ERR, 1));
		while (current->content_xpand[y] != NULL)
			y++;
		if (y > 1)
			return (error_int(data, current->content, AMB_REDIR_ERR, 1));
	}
	return (0);
}

int	manage_redirections(t_data *data)
{
	if (open_fd_in_line_cmd(data) == 1)
		return (1);
	if (first_patch_pipes_redir(data) == 1)
		return (1);
	if (patch_others_redir(data) == 1)
		return (1);
	return (0);
}
