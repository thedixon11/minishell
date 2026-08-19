#include "../minishell_general.h"

void	free_token_ll(t_token **token)
{
	t_token	*current;
	t_token	*next;

	if (token == NULL || *token == NULL)
		return ;
	current = *token;
	while (current != NULL)
	{
		next = current->next;
		if (current->value != NULL)
			ft_free((void **)&current->value);
		ft_free((void **)&current);
		current = next;
	}
	*token = NULL;
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

	if (line_cmd == NULL || *line_cmd == NULL)
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
