#include "../minishell_general.h"

void	free_env_node(t_env *to_delete)
{
	ft_free((void **)&to_delete->name);
	ft_free((void **)&to_delete->content);
	ft_free((void **)&to_delete);
}

void	delete_node(t_env *to_delete)
{
	t_env	*before;
	t_env	*after;

	before = to_delete->prev;
	after = to_delete->next;
	if (after != NULL)
		after->prev = before;
	if (before != NULL)
		before->next = after;
	free_env_node(to_delete);
}

int	remove_the_env_var(t_data *data, char *env_var_to_rm)
{
	t_env	*current;
	t_env	*to_delete;
	int		size;

	current = data->env;
	to_delete = NULL;
	size = ft_strlen(env_var_to_rm) + 1;
	while (current != NULL)
	{
		if (ft_strncmp(env_var_to_rm, current->name, size) == 0)
		{
			if (current->prev == NULL)
				data->env = data->env->next;
			to_delete = current;
			current = current->next;
			delete_node(to_delete);
		}
		else
			current = current->next;
	}
	return (0);
}

int	ft_unset(t_data *data, char **cmd_args)
{
	int	y;

	y = 1;
	if (data->env == NULL)
		return (0);
	while (cmd_args[y] != NULL)
	{
		remove_the_env_var(data, cmd_args[y]);
		y++;
	}
	return (0);
}
