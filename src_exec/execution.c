#include "../minishell_general.h"
#include "minishell_xecution.h"

void  dup2_rest(t_data *data, int current_cmd_nb)
{
  t_line  *current;

  current = data->line_cmd;
  while (current != NULL && current->cmd_nb != current_cmd_nb)
		current = current->next;
	while (current != NULL && data->error == 0 && current->cmd_nb == current_cmd_nb)
	{
		if (data->error == 0 && (current->type == T_INPUT || current->type == T_HEREDOC))
			data->error = dup2(current->fd, STDIN_FILENO);
		else if (current->type == T_OUTPUT_APPEND || current->type == T_OUTPUT_TRUNC)
			data->error = dup2(current->fd, STDOUT_FILENO);
		data->saved_errrno = errno;
	  current = current->next;
	}
  if (data->error != 0)
    ft_error_child(data, B_TRUE, "dup2", 1);
}

void  first_dup2_pipes(t_data *data, int current_cmd_nb)
{
  t_line  *current;
 
  current = data->line_cmd;
  while (current != NULL && current->cmd_nb != current_cmd_nb)
			current = current->next;
  while (current != NULL && data->error == 0 && current->cmd_nb == current_cmd_nb)
  {
    if (current->type == T_PIPE_IN)
		  data->error = dup2(current->fd, STDIN_FILENO);
    else if (data->error != 0 && current->type == T_PIPE_OUT)
			data->error = dup2(current->fd, STDOUT_FILENO);
	data->saved_errno = errno;
    current = current->next;
  }
  if (data->error != 0)
    ft_error_child(data, B_TRUE, "dup2", 1);
}

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

void	child_process(t_data *data, int current_cmd_nb)
{
	t_line	*current;
	t_cmd	*cmd_data;

	close(data->pipe_fd[0]);
	check_and_prepare_fds(data, current_cmd_nb);
    first_dup2_pipes(data, current_cmd_nb);
    dup2_rest(data, current_cmd_nb);
  	current = data->line_cmd;
	while (current->type != T_COMMAND || current->cmd_nb != current_cmd_nb)
		current = current->next;
	cmd_data = execve_preparation(data, current->content_xpand);
	free_and_close_life(data);
	if (execve(cmd_data->prog_fullname, cmd_data->args_array, cmd_data->env) == -1)
	{
		data->saved_errno = errno;
	    ft_error_child(data, B_TRUE, "execve", 1);
	}
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
	if (current_cmd_nb <= data->max_cmd_nb)
	{
		data->old_read_fd = data->pipe_fd[0];
		//wait(NULL); // NOTE: faut voir si ce wait il est pertinent ou pas
		close(data->pipe_fd[1]);
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
//
int	execute_cmds(t_data *data)
{
	int	pid;
	int	current_cmd_nb;

	current_cmd_nb = 0;
	while (current_cmd_nb <= data->max_cmd_nb)
	{
		if (pipe(data->pipe_fd) == -1)
		{
			data->saved_errno = errno;
			return (ft_error_parent_int(data, B_TRUE, "pipe", 1));
		}
		pid = fork();
		data->saved_errno = errno;
		if (pid == -1)
			return (ft_error_parent_int(data, B_TRUE, "fork", 1));
		else if (pid == 0)
			child_process(data, current_cmd_nb);
		else if (pid > 0)
			parent_process(data, current_cmd_nb);
	  current_cmd_nb++;
  }
  wait_all_children(data);
	if (data->old_read_fd >= 0)
		close(data->old_read_fd);
	return (0);
}

// NOTE: execution process start here. There is two steps:
// 1) execution of all heredocs;
// 2) check all input and output redirections (not pipe)
// 3) execution of the commands;

int execution(t_data *data)
{
	int error;

	error = val_manager(data);
	if (error == 0)
		error = heredoc_exec(data);
	if (error == 0)
		error = execute_cmds(data);
	free_and_close_life(data);
	return (error);
}
