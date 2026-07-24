#include "../minishell_general.h"

t_bool	exec_builtin_or_not(t_data *data)
{
	t_line	*current;
	int		size;

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

int	builtin_execution(t_data *data, t_bool do_i_parent)
{
	t_line	*current;
	int		size;

	current = data->line_cmd;
	while (current != NULL && current->type != T_COMMAND)
		current = current->next;
	size = ft_strlen(current->content_xpand[0]) + 1;
	if (ft_strncmp(current->content_xpand[0], "export", size) == 0 && do_i_parent == B_TRUE)
		return (ft_export(data, current->content_xpand));
	if (ft_strncmp(current->content_xpand[0], "echo", size) == 0 && do_i_parent == B_FALSE)
		return (ft_echo(data, current->content_xpand));
	return (0);
}
