#include "../minishell_general.h"
#include "minishell_xecution.h"

t_line	*move_current_to_start(t_data *data)
{
	t_line	*current;

	current = data->line_cmd;
	while (current != NULL && current->cmd_nb != data->current_cmd_nb)
		current = current->next;
	return (current);
}

// TODO: have to add the fact he will just check the nodes of the 
// right number cmd

// NOTE: The function open_fd_in_line_cmd will open all fds, depending on what
// do we have for elements in the command. We will add the fds in the node.
// It will be useful at the moment (in the child) we'll dup2 in serie.
// Here the elements needs to have a fd (if it exists):
// a) T_PIPE_IN -> old_read_fd
// b) T_PIPE_OUT -> pipe_fd[1];
// c) INPUT REDIRECTION -> open an input file
// d) OUTPUT REDIRECTION TRUNCATE -> open an output file;
// e) OUTPUT REDIRECTION APPEND -> open an output file;
// f) HEREDOC -> create a fd with pipe function

void	open_fd_in_line_cmd(t_data *data)
{
	t_line	*current;

	current = move_current_to_start(data);
	while (current != NULL && current->cmd_nb == data->current_cmd_nb)
	{
		if (current->type == T_PIPE_IN)
			current->fd = data->old_read_fd;
		else if (current->type == T_INPUT)
			current->fd = open(current->content, O_RDONLY);
		else if (current->type == T_HEREDOC)
			current->fd = data->heredoc_pipe_fds[0];
		else if (current->type == T_OUTPUT_APPEND)
			current->fd = open(current->content, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else if (current->type == T_OUTPUT_TRUNC)
			current->fd = open(current->content, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		else if (current->type == T_PIPE_OUT)
			current->fd = data->pipe_fd[1];
		data->saved_errno = errno;
		if (current->fd < 0 && current->type != T_COMMAND)
			ft_error_child(data, current->content_xpand[0], 1);
		current = current->next;
	}
}

t_bool	check_in_out_one_file(t_data *data)
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
				ft_error_child(data, MALLOC_ERR, 1);
			return (B_FALSE);
		}
		current = current->next;
	}
	return (B_TRUE);
}

void	check_and_prepare_fds(t_data *data)
{
	if (check_in_out_one_file(data) == B_FALSE)
		ft_error_child_amb_redir(data, data->failed_content, 1);
	open_fd_in_line_cmd(data);
}
