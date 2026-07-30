#include "../minishell_general.h"

void	free_cmd_data(t_data *data)
{
	if (data->cmd_data.args_tab != NULL)
		ft_free_tab(&data->cmd_data.args_tab);
	if (data->cmd_data.path_tab != NULL)
		ft_free_tab(&data->cmd_data.path_tab);
	if (data->cmd_data.env != NULL)
		ft_free_tab(&data->cmd_data.env);
	if (data->cmd_data.prog_fullname != NULL)
		ft_free((void **)&data->cmd_data.prog_fullname);
}

void	dup2_process(t_data *data, int *fd1, int fd2)
{
	data->error = dup2(*fd1, fd2);
	data->saved_errno = errno;
	ft_close_fd(fd1);
}

t_line	*move_current_to_start(t_data *data)
{
	t_line	*current;

	current = data->line_cmd;
	while (current != NULL && current->cmd_nb != data->current_cmd_nb)
		current = current->next;
	return (current);
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

void	free_and_close_life(t_data *data)
{
	close_line_cmd_fds(data);
	ft_close_fd(&data->saved_stdin);
	ft_close_fd(&data->saved_stdout);
	close_data_fds(data);
	free_line_cmd(data->line_cmd);
	free_env(data->env);
	ft_free((void **)&data->cwd);
	ft_free((void **)&data->old_cwd);
	ft_free((void **)&data);
}
