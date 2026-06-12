#include "minishell_xecution.h"

// NOTE: The child process has four missions:
// 1) check if all in/ot redirections are valid or not;
// 2) patch the input/output rediderctions using dup2.
// 3) preparing the material to execute the command;
// 4) execute the command;
//
// NOTE: To know which redirection (input/output) will be the one to be used,
// we'll dup2 in serie following the line_cmd order. The last dup2 will define
// intput/output.
//
// NOTE: The child READ FD is useless, we can directly close it.
//
// TODO: have to see how to exit correctly the child

void	child_process(t_data *data, t_line *line_cmd, int current_cmd_nb)
{
	t_line	*current;
	t_cmd	*cmd_data;

	current = line_cmd;
	close(data->pipe_fd[0]);
	if (check_and_prepare_fds(line_cmd, current_cmd_nb) == B_TRUE)
	{
		while (current->cmb_nb != current_cmd_nb && current != NULL)
			current = current->next;
		while (current->cmd_nb == current_cmd_nb && current != NULL)
		{
			if (current->type == T_PIPE_IN || current->type == T_INPUT
				|| current->type == T_HEREDOC)
				dup2(current->fd, STDIN_FILENO);
			else if (current->type == T_OUTPUT_APPEND
				|| current->type == T_OUTPUT_TRUNC
				|| current->type == T_PIPE_IN)
				dup2(current->fd, STDOUT_FILENO);
			current = current->next;
		}
		current = line_cmd;
		while (current->type != T_COMMAND && current->cmd_nb == current_cmd)
			current = current->next;
		cmd_data = execve_preparation(data, current->content_xpand);
	}
	free_and_close_life(data, line_cmd);
	exit(0);
}

// NOTE: the only main mission of the parent_process is to store the
// READ_FD to give it to the input pipe redirerction of the next child;
//
// TODO: have to check again that is the do_i_wait business ...;

void	parent_process(t_data *data, int current_cmd_nb)
{
	if (current_cmd_nb > 0)
		close(data->old_read_fd);
	if (current_cmd_nb <= data->max_cmd)
	{
		data->old_read_fd = data->pipe_fd[0];
		if (data->do_i_wait == 1)
		{
			wait(NULL);
			data->do_i_wait = 0;
		}
		close(data->pipe_fd[1]);
	}
	data->y++;
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
//
void	execute_cmds(t_data *data, t_line *line_cmd)
{
	int	pid;
	int	current_cmd_nb;

	current_cmd_nb = 0;
	while (current_cmd_nb <= data->max_cmd_nb)
	{
		if (pipe(data->pipe_fd) == -1)
			errors_exit(data, PIPE_ERR, 0, 0);
		pid = fork();
		if (pid == -1)
			errors_exit(data, FORK_ERR, 0, 0);
		else if (pid == 0)
			child_process(data, line_cmd, current_cmd_nb);
		else if (pid > 0)
			parent_process(data, current_cmd_nb);
	}
	current_cmd_nb++;

	while	(wait(NULL) > 0)
		;
	if (data->old_read_fd >= 0)
		close(data->old_read_fd);
}

// NOTE: execution process start here. There is two steps:
// 1) execution of all heredocs;
// 2) check all input and output redirections (not pipe)
// 2) execution of the commands;

void	*execution(t_data *data, t_line *line_cmd, t_env *env)
{
	heredoc_exec(data, line_cmd);
	execute_cmds(data, line_cmd, env);
	close_all_fd(line_cmd);
	free_and_close_life(data, line_cmd);
}
