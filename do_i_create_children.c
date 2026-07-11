

#include <stdalign.h>
void	open_file_descriptors(t_data *data)
{
	t_line	*current;

	current = move_current_to_start(data);
	while (current != NULL && current->cmd_nb == data->current_cmd_nb)
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
			current->fd = open(current->content, O_WRONLY | O_CREAT | O_TRUNC,
					0644);
		else if (current->type == T_PIPE_OUT)
			current->fd = data->pipe_fd[1];
		data->saved_errno = errno;
		if (current->fd < 0 && current->type != T_COMMAND)
			ft_error_builtin();
		current = current->next;
	}
}

t_bool	check_ambiguous_redir(t_data *data)
{
	t_line	*current;
	int		y;

	y = 0;
	current = move_current_to_start(data);
	while (current != NULL && current->cmd_nb == data->current_cmd_nb)
	{
		y = 0;
		if (current->type == T_INPUT || current->type == T_OUTPUT_APPEND
			|| current->type == T_OUTPUT_TRUNC)
		{
			while (current->content_xpand[y] != NULL)
				y++;
		}
		if (y > 1)
		{
			data->failed_content = ft_strdup(current->content);
			data->saved_errno = errno;
			if (!data->failed_content)
				ft_error_builtin();
			return (B_FALSE);
		}
		current = current->next;
	}
	return (B_TRUE);
}
int	check_n_patch_redir(t_data *data)
{
	if (check_ambigious_redir(data) == B_FALSE)
		ft_error_builtin();
	open_file_descriptors(data);
}

int	execute_builtin(t_data *data)
{
	t_line	*current;

	current = move_current_to_cmd(data);
	if (strncmp(current->content_xpand[0], "export", 7) == 0)
		ft_export(data);
	else if (strncmp(current->content_xpand[0], "echo", 5) == 0)
		ft_echo(data);

}

int	do_i_builtin(t_data *data)
{
	if (data->max_cmd_nb != 0)
		return (1);
	if (check_n_patch_redir(data) == 1)
		return (1);
	if (execute_builtin(data) == 1)
		return (1);
	return (0)
}
