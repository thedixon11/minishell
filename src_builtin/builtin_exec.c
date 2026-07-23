#include "../minishell_general.h"

t_bool	exec_builtin_or_not(t_data *data)
{
	t_line	*current;
	int	size;

	size = 0;
	current = data->line_cmd;
	while (current != NULL && current->type != T_COMMAND)
		current = current->next;
	size = ft_strlen(current->content_xpand[0]) + 1;
	if (current == NULL)
		return (B_FALSE);
	if (ft_strncmp(current->content_xpand[0], "export", size) == 0)
		return (B_TRUE);
	return (B_FALSE);
}

void	builtin_execution(t_data *data)
{
	t_line	*current;
	int	size;

	current = data->line_cmd;
	while (current != NULL && current->type != T_COMMAND)
		current = current->next;
	size = ft_strlen(current->content_xpand[0]) + 1;
	if (ft_strncmp(current->content_xpand[0], "export", size) == 0)
		ft_export(data, data->env, current->content_xpand);
}
