#include "../minishell_general.h"
#include "minishell_xecution.h"

void	close_used_fd(t_data *data)
{
	t_line	*current;

	current = move_current_to_start(data);
	while (current != NULL && current->cmd_nb == data->current_cmd_nb)
	{
		if (current->type == T_INPUT || current->type == T_HEREDOC)
			ft_close_fd(&current->fd);
		else if (current->type == T_OUTPUT_APPEND 
				|| current->type == T_OUTPUT_TRUNC)
			ft_close_fd(&current->fd);
		else if (current->type == T_PIPE_IN || current->type == T_PIPE_OUT)
			ft_close_fd(current->fd_of_pipe);
		current = current->next;		
	}
	ft_close_fd(&data->pipe_fd[1]);
}
void	save_pipe_rd_to_old_read_fd(t_data *data)
{
	if (data->current_cmd_nb < data->max_cmd_nb)
		data->old_read_fd = data->pipe_fd[0];
}

void	wait_all_children(t_data *data)
{
	int	status;

	while (waitpid(-1, &status, 0) != -1)
	{
		if (WIFEXITED(status))
			data->code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			data->code = 128 + WTERMSIG(status);
	}
}

int	reset_redir_patch(t_data *data)
{
	
	if (dup2(data->saved_stdin, STDIN_FILENO) == -1)
	{
		data->saved_errno = errno;
		return (ft_error_parent_int(data, DUP2_ERR, 1));
	}
	if (dup2(data->saved_stdout, STDOUT_FILENO) == -1)
	{
		data->saved_errno = errno;
		return (ft_error_parent_int(data, DUP2_ERR, 1));
	}
	return (0);
}

int	execute_cmds(t_data *data)
{
	while (data->current_cmd_nb <= data->max_cmd_nb)
	{
		if (reset_redir_patch(data) == 1)
			return (1);
		if (exec_builtin_or_not(data) == B_TRUE)
			builtin_execution(data, B_TRUE);
		else if (classic_execution(data) == 1)
			return (1);
		//if (classic_execution(data) == 1)		// BUG: je dois voir si pertinent ou pas
			//close_used_fd(data);
		save_pipe_rd_to_old_read_fd(data);
		data->current_cmd_nb++;
	}
	wait_all_children(data);
	return (0);
}
