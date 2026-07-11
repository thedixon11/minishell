#include "../minishell_general.h"
#include "minishell_xecution.h"

int	store_stdin_stdout(t_data *data)
{
	data->saved_stdin = dup(STDIN_FILENO);
	if (data->saved_stdin == -1)
		return (ft_error_parent_int(data, DUP2_ERR, 1));
	data->saved_stdout = dup(STDOUT_FILENO);
	if (data->saved_stdout == -1)
		return (ft_error_parent_int(data, DUP2_ERR, 1));
	return (0);
}

int	execution_start(t_data *data)
{
	int	error;
	int	code;

	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->old_read_fd = -1;
	error = store_stdin_stdout(data);
	if (error == 0)
		error = val_manager(data);
	if (error == 0)
		error = heredoc_exec(data);
	if (error == 0)
		error = execute_cmds(data);
	code = data->code;
	free_and_close_life(data);
	return (code);
}
