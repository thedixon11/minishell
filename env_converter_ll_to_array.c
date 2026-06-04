#include "minishell_xecution.h"

// NOTE: rebuld_value have the mission to fusion name of all env_var with their
// respective content and '=' between them.

char	*rebuild_value(t_env *current)
{
	char	*temp;
	char	*rebuild_value;

	temp = ft_strjoin(current->name, "=");
	rebuild_value = ft_strjoin(temp, current->content);
	free(temp);
	return (rebuild_value);
}

// NOTE: before executing the command, it's necessary to convert the
// environment from linked list to array, because execve need it in this
// format. That's the job of env_converter_ll_to_array. To do that,
// we need:
// 1) count how many env_var exists in the environment;
// 2) have to rebuild the values
// (we have to join name, '=' and content together)

char	**env_converter_ll_to_array(t_env *env)
{
	t_env	*current;
	int		y;
	char	**converted_env;

	y = 0;
	current = env;
	while (current != NULL)
	{
		current = current->next;
		y++;
	}
	converted_env = ft_calloc(y + 1, sizeof(char *));
	if (!converted_env)
		return (NULL);
	current = env;
	y = 0;
	while (current != NULL)
	{
		converted_env[y] = rebuild_value(current);
		current = current->next;
		y++;
	}
	return (converted_env);
}
