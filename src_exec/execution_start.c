#include "../minishell_general.h"

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
		return (error_int(data, I_DUP, strerror(errno), 1));
	data->saved_stdout = dup(STDOUT_FILENO);
	if (data->saved_stdout == -1)
		return (error_int(data, I_DUP, strerror(errno), 1));
	return (0);
}

t_data	*data_creation(t_mini *mini)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
	{
		error_int(data, I_CALLOC, LIBFT_ERR, 1);
		return (NULL);
	}
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->old_read_fd = -1;
	data->env = mini->env;
	data->line_cmd = mini->line_cmd;
	data->max_cmd_nb = mini->max_cmd_nb;
	data->code = mini->code;
	return (data);
}

int	execution_start(t_mini *mini)
{
	int	error;
	char	*check_dir;
	t_data	*data;

	data = data_creation(mini);
	set_fd_pipe_zero(data);
	data->do_i_exit = B_FALSE;
	error = store_stdin_stdout(data);
	if (error == 0)
		error = val_manager(data);
	if (error == 0)
		error = heredoc_exec(data);
	if (error == 0)
		error = execute_cmds(data);
	code = data->code;
	reset_redir_patch(data);

  // NOTE: just some checker to print (5 below lines)
	
	check_dir = getcwd(NULL, 0);
	ft_printf("|\ncwd = %s\n", check_dir);
	ft_free((void **)&check_dir);
	ft_printf("cwd data = %s\n", data->cwd);
	ft_printf("oldcwd data = %s\n", data->old_cwd);


	free_and_close_life(data);
	return (code);
}
