#include "../minishell_general.h"
#include "minishell_xecution.h"

void	close_used_fd(t_data *data)
{
	t_line	*current;

	current = move_current_to_start(data);
	while (current != NULL && current->cmd_nb == data->current_cmd_nb)
	{
		if (current->type == T_INPUT || current->type == T_PIPE_IN
			|| current->type == T_HEREDOC)
			ft_close_fd(&current->fd);
		else if (current->type == T_OUTPUT_APPEND 
				|| current->type == T_OUTPUT_APPEND
				|| current->type == T_PIPE_OUT)
			ft_close_fd(&current->fd);
		current = current->next;		
	}
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
		/*
		if (exec_builtin_or_not(data) == B_TRUE)
			builtin_execution(data);
		else if (classic_execution(data) == 1)
			return (1);*/
		classic_execution(data);
		parent_process(data);
		close_used_fd(data);
		data->current_cmd_nb++;
	}
	wait_all_children(data);
	return (0);
}
