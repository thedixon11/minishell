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
			ft_free((void **)&content);
			ft_free_tab((&content_xpand);
			ft_free((void **)&current);
		}
		current = current->next;
	}
}

int	ft_unset(t_data *data, char **cmd_args)
{
	int	y;

	y = 1;
	while (cmd_args[y] != NULL)
	{
		find_env_var_and_unset(data, cmd_args[y]);
		y++;
	}
	return (0);
}
