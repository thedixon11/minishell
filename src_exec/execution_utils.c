#include "../minishell_general.h"

void	free_cmd_data(t_cmd *cmd_data)
{
	if (cmd_data->prog_fullname != NULL)
		ft_free((void **)&cmd_data->prog_fullname);
	if (cmd_data->args_tab != NULL)
		ft_free_tab(&cmd_data->args_tab);
	if (cmd_data->path_tab != NULL)
		ft_free_tab(&cmd_data->path_tab);
	if (cmd_data->env != NULL)
		ft_free_tab(&cmd_data->env);
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

void	close_all_fd(t_line *line_cmd)
{
	t_line	*current;

	current = line_cmd;
	while (current != NULL)
	{
		ft_close_fd(&current->fd);
		current = current->next;
	}
}

void	free_and_close_life(t_data *data)
{
	close_all_fd(data->line_cmd);
	free_line_cmd(data->line_cmd);
	free_env(data->env);
	ft_free((void **)&data);
}
