#include "../minishell_general.h"

void	close_data_fds(t_data *data)
{
	ft_close_fd(&data->saved_stdin);
	ft_close_fd(&data->saved_stdout);
	ft_close_fd(&data->old_read_fd);
	ft_close_fd(&data->pipe_fd[0]);
	ft_close_fd(&data->pipe_fd[1]);
}

void	close_line_cmd_fds(t_data *data)
{
	t_line	*current;

	current = data->line_cmd;
	while (current != NULL)
	{
		if (current->type != T_PIPE_IN && current->type != T_PIPE_OUT)
			ft_close_fd(&current->fd);
		else
			ft_close_fd(current->fd_of_pipe);
		current = current->next;
	}
}
