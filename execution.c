#include "minishell_xecution.h"

// NOTE: The child process has three missions:
// 1) patch the input/output rediderctions using dup2.
// 2) preparing the material to execute the command;
// 3) execute the command;
//
// NOTE: To know which redirection (input/output) will be the one to be used,
// we'll dup2 in serie following the line_cmd order. The last dup2 will define
// intput/output.
//
// NOTE: The child READ FD is useless, we can directly close it.
//
// TODO: We have to free and close everything after the execve

void	child_process(t_data *data, t_line *line_cmd, int current_cmd)
{
	t_line	*current;
	t_cmd	*cmd_data;

	current = line_cmd;
	close(data->pipe_fd[0]);
	while (current->cmb_nb != current_cmd && current != NULL)
		current = current->next;
	while (current->cmd_nb == current_cmd && current != NULL)
	{
		if (current->type == T_PIPE_IN || current->type == T_INPUT
			|| current->type == T_HEREDOC)
			dup2(current->fd, STDIN_FILENO);
		else if (current->type == T_OUTPUT_APPEND
			|| current->type == T_OUTPUT_TRUNC || current->type == T_PIPE_IN)
			dup2(current->fd, STDOUT_FILENO);
		current = current->next;
	}
	current = line_cmd;
	while (current->type != T_COMMAND && current->cmd_nb == current_cmd)
		current = current->next;
	cmd_data = execve_preparation(data, current->content);
}

// NOTE: the only main mission of the parent_process is to store the
// READ_FD to give it to the input pipe redicerction of the next child;
//
// TODO: have to check again that is the do_i_wait business ...;

void	parent_process(t_data *data, int current_cmd)
{
	if (current_cmd > 0)
		close(data->old_read_fd);
	if (current_cmd <= data->max_cmd)
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

// NOTE: The function open_fd_in_line_cmd will open all fds, depending on what
// do we have for elements in the command. We will add the fds in the node.
// It will be useful at the moment (in the child) we'll dup2 in serie.
// Here the elements needs to have a fd (if it exists):
// a) T_PIPE_IN -> old_read_fd
// b) T_PIPE_OUT -> pipe_fd[1];
// c) INPUT REDIRECTION -> open an input file
// d) OUTPUT REDIRECTION TRUNCATE -> open an output file;
// e) OUTPUT REDIRECTION APPEND -> open an output file;
// f) HEREDOC -> create a fd with pipe function

void	open_fd_in_line_cmd(t_data *data, t_line *line_cmd, int current_cmd)
{
	t_line	*current;

	current = line_cmd;
	while (current->cmd_nb != current_cmd && current != NULL)
		current = current->next;
	while (current->cmd_nb == current_cmd && current != NULL)
	{
		if (current->type == T_PIPE_IN)
			current->fd = data->old_read_fd;
		else if (current->type == T_INPUT)
			current->fd = open(current->content, O_RDONLY);
		else if (current->type == T_HEREDOC)
			current->fd = data->heredoc_pipe_fds[0];
		else if (current->type == T_OUTPUT_APPEND)
			current->fd = open(current->content, O_WRONLY | O_CREAT | O_APPEND,
					0644);
		else if (current->type == T_OUTPUT_TRUNC)
			outfile = open(data->argv[y + 1], O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		else if (current->type == T_PIPE_OUT)
			current->fd = data->pipe_fd[1];
		current = current->next;
	}
}

// NOTE: With execute_cmds, we'll execute all cmds. For each cmds, we'll
// create a child, that will execute it. Here are the steps :
// 1) create a pipe and store it in data;
// 2) open all fds of the line_cmd;
// 3) fork;
// 4a) execute cmd with the child;
// 4b) store the read fd to send it to the next children;
//
// NOTE: The choice was made to open all fds in the parent, before
// forking. The only thing done in the children is all the in-out patching
//
// TODO: Have to rebuild all about wait and waitpid functions;

void	execute_cmds(t_data *data, t_line *line_cmd, t_env *env)
{
	int	pid;
	int	current_cmd;

	current_cmd = 0;
	while (current_cmd <= data->max_cmd)
	{
		if (pipe(data->pipe_fd) == -1)
			errors_exit(data, PIPE_ERR, 0, 0);
		open_fd_in_line_cmd(data, line_cmd);
		pid = fork();
		if (pid == -1)
			errors_exit(data, FORK_ERR, 0, 0);
		if (pid == 0)
			child_process(data, line_cmd, env, current_cmd);
		if (pid > 0)
			parent_process(data, current_cmd);
	}
	while (wait(NULL) > 0)
		;
	if (data->old_read_fd >= 0)
		close(data->old_read_fd);
}

// NOTE: execution process start here. There is two steps:
// 1) execution of all heredocs;
// 2) execution of the commands;

void	*execution(t_data *data, t_line *line_cmd, t_env *env)
{
	heredoc_exec(line_cmd);
	execute_cmds(data, line_cmd, env);
	close_all_fd();
	free_all();
}
