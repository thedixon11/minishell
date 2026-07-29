#include "../minishell_general.h"
#include "minishell_xecution.h"

void	set_fd_pipe_zero(t_data *data)
{
	t_line	*current;

	current = data->line_cmd;
	while (current != NULL)
	{
		if (current->type == T_PIPE_IN || current->type == T_PIPE_OUT)
		{
			current->fd = 0;
			current->fd_of_pipe = NULL;
		}
		current = current->next;
	}
}

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
	char	*check_dir;

	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->old_read_fd = -1;
	set_fd_pipe_zero(data);
	error = store_stdin_stdout(data);
	if (error == 0)
		error = val_manager(data);
	if (error == 0)
		error = heredoc_exec(data);
	if (error == 0)
		error = execute_cmds(data);
	code = data->code;
	reset_redir_patch(data);
	check_dir = getcwd(NULL, 0);
	ft_printf("|\ncwd = %s\n", check_dir);
	ft_free((void **)&check_dir);
	ft_printf("cwd data = %s\n", data->cwd);
	ft_printf("oldcwd data = %s\n", data->old_cwd);
	free_and_close_life(data);
	return (code);
}
