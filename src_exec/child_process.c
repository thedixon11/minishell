#include "../minishell_general.h"
#include "minishell_xecution.h"

void	dup2_rest(t_data *data)
{
	t_line	*current;

	current = data->line_cmd;
	while (current != NULL && current->cmd_nb != data->current_cmd_nb)
		current = current->next;
	while (current != NULL && data->error != -1
		&& current->cmd_nb == data->current_cmd_nb)
	{
		if (data->error != -1 && (current->type == T_INPUT
				|| current->type == T_HEREDOC))
			data->error = dup2(current->fd, STDIN_FILENO);
		else if (data->error != -1 && (current->type == T_OUTPUT_APPEND
				|| current->type == T_OUTPUT_TRUNC))
			data->error = dup2(current->fd, STDOUT_FILENO);
		data->saved_errno = errno;
		current = current->next;
	}
	if (data->error == -1)
		ft_error_child(data, DUP2_ERR, 1);
}

void	first_dup2_pipes(t_data *data)
{
	t_line	*current;

	current = data->line_cmd;
	while (current != NULL && current->cmd_nb != data->current_cmd_nb)
		current = current->next;
	while (current != NULL && data->error != -1
		&& current->cmd_nb == data->current_cmd_nb)
	{
		if (data->error != -1 && current->type == T_PIPE_IN)
			data->error = dup2(current->fd, STDIN_FILENO);
		else if (data->error != -1 && current->type == T_PIPE_OUT)
			data->error = dup2(current->fd, STDOUT_FILENO);
		data->saved_errno = errno;
		current = current->next;
	}
	if (data->error == -1)
		ft_error_child(data, DUP2_ERR, 1);
}

void	check_cmd_is_not_empty(t_data *data, t_line *current)
{
	if (current->content_xpand == NULL)
	{
		free_and_close_life(data);
		exit(0);
	}
	if (current->content_xpand[0][0] == 0)
	{
		if (ft_strchr(current->content, '"') != 0)
			ft_error_child_cmd_not_found(data, "", 1);
	}
}

t_line	*move_current_to_cmd(t_data *data)
{
	t_line	*current;

	current = data->line_cmd;
	while (current != NULL && (current->type != T_COMMAND
			|| current->cmd_nb != data->current_cmd_nb))
		current = current->next;
	return (current);
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

void	child_process(t_data *data)
{
	t_line	*current;
	t_cmd	*cmd_data;

	ft_close_fd(&data->pipe_fd[0]);
	check_and_prepare_fds(data);
	first_dup2_pipes(data);
	dup2_rest(data);
	current = move_current_to_cmd(data);
	check_cmd_is_not_empty(data, current);
	cmd_data = execve_preparation(data, current->content_xpand);
	free_and_close_life(data);
	execve(cmd_data->prog_fullname, cmd_data->args_tab, cmd_data->env);
	data->saved_errno = errno;
	ft_error_child(data, EXECVE_ERR, 1);
}
