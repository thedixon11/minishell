#include "../minishell_general.h"
#include "minishell_xecution.h"

int	time_to_fork_and_exec(t_data *data)
{
	int	pid;

	pid = fork();
	data->saved_errno = errno;
	if (pid == -1)
		return (ft_error_parent_int(data, FORK_ERR, 1));
	else if (pid == 0)
		child_process(data);
	return (0);
}

int	time_to_pipe(t_data *data)
{
	if (data->max_cmd_nb > 0 && pipe(data->pipe_fd) == -1)
	{
		data->saved_errno = errno;
		return (ft_error_parent_int(data, PIPE_ERR, 1));
	}
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
