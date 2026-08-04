#include "../minishell_general.h"

void	free_cmd_args(t_data *data)
{
	if (data->cmd_data != NULL)
	{
		if (data->cmd_data->prog_fullname != NULL)
			ft_free((void **)&data->cmd_data->prog_fullname);
		if (data->cmd_data->args_tab != NULL)
			ft_free_tab(&data->cmd_data->args_tab);
		if (data->cmd_data->path_tab != NULL)
			ft_free_tab(&data->cmd_data->path_tab);
		if (data->cmd_data->env != NULL)
			ft_free_tab(&data->cmd_data->env);
		if (data->cmd_data != NULL)
			ft_free((void **)&data->cmd_data);
	}
}

void	free_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current->next != NULL)
	{
		if (current->name != NULL)
			ft_free((void **)&current->name);
		if (current->content != NULL)
			ft_free((void **)&current->content);
		current = current->next;
		if (current->prev != NULL)
			ft_free((void **)&current->prev);
	}
	if (current->name != NULL)
		ft_free((void **)&current->name);
	if (current->content != NULL)
		ft_free((void **)&current->content);
	ft_free((void **)&current);
}

void	free_line_cmd(t_line *line_cmd)
{
	t_line	*current;

	current = line_cmd;
	while (current->next != NULL)
	{
		if (current->content != NULL)
			ft_free((void **)&current->content);
		if (current->content_xpand != NULL)
			ft_free_tab(&current->content_xpand);
		current = current->next;
		ft_free((void **)&current->prev);
	}
	if (current->content != NULL)
		ft_free((void **)&current->content);
	if (current->content_xpand != NULL)
		ft_free_tab(&current->content_xpand);
	ft_free((void **)&current);
}
