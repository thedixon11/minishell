#include "../minishell_general.h"

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

t_bool	do_i_parent(t_data *data)
{
	if (is_it_builtin(data) == B_FALSE)
		return (B_FALSE);
	if (is_echo_pwd_env(data) == B_FALSE)
		return (B_FALSE);
	if (is_there_pipes(data) == B_TRUE)
		return (B_FALSE);
	return (B_TRUE);
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
		return (error_int(data, I_DUP2, strerror(errno), 1));
	if (dup2(data->saved_stdout, STDOUT_FILENO) == -1)
		return (error_int(data, I_DUP2, strerror(errno), 1));
	return (0);
}

int	execute_cmds(t_data *data)
{
	while (data->current_cmd_nb <= data->max_cmd_nb)
	{
		if (reset_redir_patch(data) == 1)
			return (1);
		if (do_i_parent(data) == B_TRUE)
			execute_builtin_parent(data);
		else
			classic_execution(data);
		close_used_fd(data);
		save_pipe_rd_to_old_read_fd(data);
		data->current_cmd_nb++;
	}
	wait_all_children(data);
	//export_no_args(data);
	return (0);
}
