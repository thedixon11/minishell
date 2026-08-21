#include "../minishell_general.h"

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
	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
}

void	wait_all_children(t_data *data)
{
	int	status;
	int	pid;

	pid = waitpid(-1, &status, 0);
	while (pid > 0)
	{
		if (pid == data->last_pid)
		{
			if (WIFEXITED(status))
				data->code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				data->code = 128 + WTERMSIG(status);
		}
		pid = waitpid(-1, &status, 0);
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
	init_signal_parent();
	while (data->current_cmd_nb <= data->max_cmd_nb)
	{
		if (reset_redir_patch(data) == 1)
			return (1);
		if (is_there_command(data) == B_FALSE)
			no_command_process(data);
		else if (do_i_parent(data) == B_TRUE)
			data->code = execute_builtin_parent(data);
		else
			classic_execution(data);
		close_used_fd(data);
		save_pipe_rd_to_old_read_fd(data);
		data->current_cmd_nb++;
	}
	wait_all_children(data);
	handle_ctrl_c(data);
	return (0);
}
