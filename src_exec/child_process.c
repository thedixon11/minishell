#include "../minishell_general.h"
#include "minishell_xecution.h"

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

void	child_process(t_data *data)
{
	t_line	*current;
	t_cmd	*cmd_data;

	current = move_current_to_cmd(data);
	check_cmd_is_not_empty(data, current);
	cmd_data = execve_preparation(data, current->content_xpand);
	free_and_close_life(data);
	execve(cmd_data->prog_fullname, cmd_data->args_tab, cmd_data->env);
	data->saved_errno = errno;
	ft_error_child(data, EXECVE_ERR, 1);
}
