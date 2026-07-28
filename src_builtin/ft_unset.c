#include "../minishell_general.h"

int	remove_the_env_var(t_data *data, char *env_var_to_rm)
{
	t_env	*current;
	int		size;

	current = data->env;
	size = ft_strlen(env_var_to_rm) + 1;
	while (current != NULL)
	{
		if (ft_strncmp(env_var_to_rm, current->name, size) == 0)
		{
			current->prev->next = current->next;
			current->next->prev = current->prev;
			ft_free((void **)&current->content);
			ft_free((void **)&current);
		}
		current = current->next;
	}
	return (0);
}

int	ft_unset(t_data *data, char **cmd_args)
{
	int	y;

	y = 1;
	while (cmd_args[y] != NULL)
	{
		remove_the_env_var(data, cmd_args[y]);
		y++;
	}
	return (0);
}
