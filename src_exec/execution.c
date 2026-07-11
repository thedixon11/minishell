#include "../minishell_general.h"
#include "minishell_xecution.h"

// NOTE: the only main mission of the parent_process is to store the
// READ_FD to give it to the input pipe redirerction of the next child;
//
// TODO: have to check again that is the do_i_wait business ...;

void	parent_process(t_data *data)
{
	if (data->current_cmd_nb > 0)
		ft_close_fd(&data->old_read_fd);
	if (data->current_cmd_nb <= data->max_cmd_nb)
	{
		data->old_read_fd = data->pipe_fd[0];
		ft_close_fd(&data->pipe_fd[1]);
	}
}

// NOTE: With execute_cmds, we'll execute all cmds. For each cmds, we'll
// create a child, that will execute it. Here are the steps :
// 1) create a pipe and store it in data;
// 2) fork;
// 3a) execute cmd with the child;
// 3b) store the read fd to send it to the next children;
//
// NOTE: The choice was made to open all fds in the parent, before
// forking. The only thing done in the children is all the in-out patching
//
// TODO: Have to rebuild all about wait and waitpid functions;
//
// TODO: If there is an error in the input/output redirections ,
// we have to close all the fds of the cmd number before going on
// and the old_read_fd. But we have to secure that the next pipe node
// will not be open
//

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

int	execute_cmds(t_data *data)
{
	int	pid;

	while (data->current_cmd_nb <= data->max_cmd_nb)
	{
		if (data->max_cmd_nb > 0 && pipe(data->pipe_fd) == -1)
		{
			data->saved_errno = errno;
			return (ft_error_parent_int(data, PIPE_ERR, 1));
		}
		pid = fork();
		data->saved_errno = errno;
		if (pid == -1)
			return (ft_error_parent_int(data, FORK_ERR, 1));
		else if (pid == 0)
			child_process(data);
		else if (pid > 0)
			parent_process(data);
		data->current_cmd_nb++;
	}
	wait_all_children(data);
	if (data->old_read_fd >= 0)
		ft_close_fd(&data->old_read_fd);
	return (0);
}

// NOTE: execution process start here. There is two steps:
// 1) execution of all heredocs;
// 2) check all input and output redirections (not pipe)
// 3) execution of the commands;

int	execution(t_data *data)
{
	int	error;
	int	code;

	data->pipe_fd[0] = -1;
	data->pipe_fd[1] = -1;
	data->old_read_fd = -1;
	error = val_manager(data);
	if (error == 0)
		error = heredoc_exec(data);
	if (error == 0)
		error = execute_cmds(data);
	code = data->code;
	free_and_close_life(data);
	return (code);
}
