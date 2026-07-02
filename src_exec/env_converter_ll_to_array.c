#include "../minishell_general.h"

// NOTE: rebuld_value have the mission to fusion name of all env_var with their
// respective content and '=' between them.

char	*rebuild_value(t_data *data, t_env *current)
{
	char	*temp;
	char	*rebuild_value;

	temp = ft_strjoin(current->name, "=");
	if (!temp)
	{
		data->saved_errno = errno;
		return (NULL);
	}
	rebuild_value = ft_strjoin(temp, current->content);
	if (!rebuild_value)
	{
		data->saved_errno = errno;
		ft_free(&temp);
		return (NULL);
	}
	ft_free(&temp);
	return (rebuild_value);
}

// NOTE: before executing the command, it's necessary to convert the
// environment from linked list to array, because execve need it in this
// format. That's the job of env_converter_ll_to_array. To do that,
// we need:
// 1) count how many env_var exists in the environment;
// 2) have to rebuild the values
// (we have to join name, '=' and content together)

char	**env_converter_ll_to_array(t_data *data, t_env *env)
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
		ft_error_child(data, B_TRUE, "malloc", 1);
	current = env;
	y = 0;
	while (current != NULL)
	{
		converted_env[y] = rebuild_value(data, current);
		if (rebuild_value == NULL)
		{
			errno = data->saved_errno;
			ft_error_child(data, B_TRUE, "malloc", 1);
		}
		current = current->next;
		y++;
	}
	return (converted_env);
}
