#include "../minishell_general.h"
#include "minishell_xecution.h"

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
	close_data_fds(data);
	free_line_cmd(data->line_cmd);
	free_env(data->env);
	ft_free((void **)&data);
}
