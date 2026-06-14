#include "minishell_xecution.h"

void	free_cmd_data(t_cmd *cmd_data)
{
	if (cmd_data->prog_fullname != NULL)
		free(cmd_data->prog_fullname);
	if (cmd_data->args_array != NULL)
		ft_free_tab(cmd_data->args_array);
	if (cmd_data->path_array != NULL)
		ft_free_tab (cmd_data->path_array);
	if (cmd_data->env != NULL)
		ft_free_tab(cmd_data->env);
}

void	free_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (env->next != NULL)
	{
		if (current->name != NULL)
			free(current->name);
		if (current->content != NULL)
			free(current->content);
		current = current->next;
		free(current->prev);
	}
	if (current->name != NULL)
		free(current->name);
	if (current->content != NULL)
		free(current->content);
	free(current);
}

void	free_line_cmd(t_line *line_cmd)
{
	t_line	*current;

	current = line_cmd;
	while (current->next != NULL)
	{
		if (current->content != NULL)
			free(current->content);
		if (current->content_xpand != NULL)
			ft_free_tab(current->content_xpand);
		current = current->next;
		free(current->prev);
	}
	if (current->content != NULL)
		free(current->content);
	if (current->content_xpand != NULL)
		ft_free_tab (current->content_xpand);
	free(current);
}

void	close_all_fd(t_line *line_cmd)
{
	t_line	*current;

	current = line_cmd;
	while (current != NULL)
	{
		if (current->fd > -1)
			close(current->fd);
		current = current->next;
	}
}

void	free_and_close_life(t_data *data)
{
	close_all_fd(data->line_cmd);
	free_line_cmd(data->line_cmd);
	free_env(data->env);
	free(data);
}
