#include "../minishell_general.h"

void	free_state_data(t_state *state)
{
	if (state == NULL)
		return ;
	if (state->current != NULL && state->current->value != NULL)
		ft_free((void **)&state->current->value);
	if (state->current != NULL)
		ft_free((void **)&state->current);
}

void	free_token_ll(t_token *token)
{
	t_token	*current;

	if (!token)
		return ;
	current = token;
	while (current->next != NULL)
	{
		if (current->value != NULL)
			ft_free((void **)&current->value);
		current = current->next;
		ft_free((void **)&current->prev);
	}
	if (current->value != NULL)
		ft_free((void **)&current->value);
	ft_free((void **)&current);
}

void	free_cmd_args(t_data *data)
{
	if (data != NULL && data->cmd_data != NULL)
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

void	free_env(t_env **env)
{
	t_env	*current;
	t_env	*next;

	if (env == NULL && *env == NULL)
		return ;
	current = *env;
	while (current != NULL)
	{
		next = current->next;
		if (current->name != NULL)
			ft_free((void **)&current->name);
		if (current->content != NULL)
			ft_free((void **)&current->content);
		ft_free((void **)&current);
		current = next;
	}
	*env = NULL;
}

void	free_line_cmd(t_line **line_cmd)
{
	t_line	*current;
	t_line	*next;

	if (line_cmd == NULL && *line_cmd == NULL)
		return ;
	current = *line_cmd;
	while (current != NULL)
	{
		next = current->next;
		if (current->content != NULL)
			ft_free((void **)&current->content);
		if (current->content_xpand != NULL)
			ft_free_tab(&current->content_xpand);
		ft_free((void **)&current);
		current = next;
	}
	*line_cmd = NULL;
}
