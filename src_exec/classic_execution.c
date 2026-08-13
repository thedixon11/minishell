#include "../minishell_general.h"

int	time_to_fork_and_exec(t_data *data)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		return (error_int(data, I_FORK, strerror(errno), 1));
  if (data->current_cmd_nb +  1 == data->max_cmd_nb)
    data->last_pid = B_TRUE;
	else if (pid == 0)
		child_process(data);
	return (0);
}

int	time_to_pipe(t_data *data)
{
	if (data->max_cmd_nb > 0 && pipe(data->pipe_fd) == -1)
		return (error_int(data, I_PIPE, strerror(errno), 1));
	return (0);
}

void	classic_execution(t_data *data)
{
	if (data->current_cmd_nb < data->max_cmd_nb && time_to_pipe(data) == 1)
		return ;
	if (manage_redirections(data) == 1)
		return ;
	if (time_to_fork_and_exec(data) == 1)
		return ;
}
