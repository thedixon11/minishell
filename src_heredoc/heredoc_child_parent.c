#include "../minishell_general.h"

void	heredoc_parent(t_data *data, int *error)
{
	ft_close_fd(&data->heredoc_pipe_fds[1]);
	wait_all_children(data);
	if (g_signal == SIGINT)
	{
		*error = -1;
		handle_ctrl_c(data);
		init_signal_prompt();
	}
}

void	heredoc_child(t_data *data, t_line *current)
{
	int	code;

	code = 0;
	init_signal_heredoc();
	rl_event_hook = heredoc_event_hook;
	ft_close_fd(&data->heredoc_pipe_fds[0]);
	if ((ft_strchr(current->content, '\'') != NULL)
		|| (ft_strchr(current->content, '\"') != NULL))
		delimiter_manager_n_write_hdoc(data, current);
	else
		write_on_fd(data, current, B_TRUE);
	code = data->code;
	free_and_close_life(data);
	exit (code);
}
