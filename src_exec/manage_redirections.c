#include "../minishell_general.h"
#include "minishell_xecution.h"
#include <unistd.h>

int	patch_others_redir(t_data *data)
{
	t_line	*current;

	current = data->line_cmd;
	while (current != NULL && current->cmd_nb != data->current_cmd_nb)
		current = current->next;
	while (current != NULL && data->error != -1
		&& current->cmd_nb == data->current_cmd_nb)
	{
		if (data->error != -1 && (current->type == T_INPUT
				|| current->type == T_HEREDOC))
			dup2_process(data, &current->fd, STDIN_FILENO);
		else if (data->error != -1 && (current->type == T_OUTPUT_APPEND
				|| current->type == T_OUTPUT_TRUNC))
			dup2_process(data, &current->fd, STDOUT_FILENO);
		current = current->next;
	}
	if (data->error == -1)
		return (ft_error_parent_int(data, DUP2_ERR, 1));
	return (0);
}

int	first_patch_pipes_redir(t_data *data)
{
	t_line	*current;

	current = data->line_cmd;
	while (current != NULL && current->cmd_nb != data->current_cmd_nb)
		current = current->next;
	while (current != NULL && data->error != -1
		&& current->cmd_nb == data->current_cmd_nb)
	{
		if (data->error != -1 && current->type == T_PIPE_IN)
			dup2_process(data, current->fd_of_pipe, STDIN_FILENO);
		else if (data->error != -1 && current->type == T_PIPE_OUT)
			dup2_process(data, current->fd_of_pipe, STDOUT_FILENO);
		current = current->next;
	}
	if (data->error == -1)
		return (ft_error_parent_int(data, DUP2_ERR, 1));
	return (0);
}

int	open_fd_in_line_cmd(t_data *data)
{
	t_line	*current;

	current = move_current_to_start(data);
	while (current != NULL && current->cmd_nb == data->current_cmd_nb)
	{
		if (current->type == T_PIPE_IN)
			current->fd_of_pipe = &data->old_read_fd;
		else if (current->type == T_INPUT)
			current->fd = open(current->content, O_RDONLY);
		else if (current->type == T_OUTPUT_APPEND)
			current->fd = open(current->content, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else if (current->type == T_OUTPUT_TRUNC)
			current->fd = open(current->content, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		else if (current->type == T_PIPE_OUT)
			current->fd_of_pipe = &data->pipe_fd[1];
		data->saved_errno = errno;
		if (current->fd < 0 && current->type != T_COMMAND)
			return (ft_error_parent_int(data, current->content_xpand[0], 1));
		current = current->next;
	}
	return (0);
}

int	check_ambiguous_redir(t_data *data)
{
	t_line	*current;
	int		y;

	y = 0;
	current = move_current_to_start(data);
	while (current != NULL && current->cmd_nb == data->current_cmd_nb)
	{
		y = 0;
		if (current->type == T_INPUT || current->type == T_OUTPUT_APPEND
			|| current->type == T_OUTPUT_TRUNC)
		{
			while (current->content_xpand[y] != NULL)
				y++;
		}
		if (y > 1)
		{
			data->failed_content = ft_strdup(current->content);
			data->saved_errno = errno;
			if (!data->failed_content)
				return (ft_error_parent_int(data, MALLOC_ERR, 1));
			return (ft_error_parent_amb_redir(data, data->failed_content, 1));
		}
		current = current->next;
	}
	return (0);
}

int	manage_redirections(t_data *data)
{
	if (check_ambiguous_redir(data) == 1)
		return (1);
	if (open_fd_in_line_cmd(data) == 1)
		return (1);
	if (first_patch_pipes_redir(data) == 1)
		return (1);
	if (patch_others_redir(data) == 1)
		return (1);
	return (0);
}
