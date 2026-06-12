#include "minishell_xecution.h"

// TODO: have to add the fact he will just check the nodes of the right number cmd


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

t_bool	open_fd_in_line_cmd(t_data *data, t_line *line_cmd, int current_cmd_nb)
{
	t_line	*current;

	current = line_cmd;
	while (current->cmd_nb != current_cmd_nb && current != NULL)
		current = current->next;
	while (current->cmd_nb == current_cmd_nb && current != NULL)
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
		if (current->fd < 0)
			return (B_FALSE);
		current = current->next;
	}
	return (B_TRUE);
}


t_bool check_in_out_one_file(t_line *line_cmd, int current_cmd_nb)
{
	t_line	*current;
	int	y;

	y = 0;
	current = line_cmd;
  while (current->cmd_nb != current_cmd_nb)
    current = current->next;
	while (current->cmd_nb == current_cmd_nb && current != NULL)
	{
		y = 0;
		if (current->type == T_INPUT || current->type == T_OUTPUT_APPEND
			|| current->type == T_OUTPUT_TRUNC)
		{
			while (current->content_xpand[y] != NULL)
				y++;
		}
		if (y > 1)
			return (B_FALSE);
		current = current->next;
	}
	return (B_TRUE);
}

t_bool	check_and_prepare_fds(t_data *data, t_line *line_cmd, int current_cmd_nb)
{
	if (check_in_out_one_file(line_cmd, current_cmd_nb) == B_FALSE)
		return (B_FALSE);
	if (open_fd_in_line_cmd(data, line_cmd, current_cmd_nb) == B_FALSE)
		return (B_FALSE);
	return (B_TRUE);
}
