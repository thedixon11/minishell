#include "../minishell_general.h"

// NOTE: rebuld_value have the mission to fusion name of all env_var with their
// respective content and '=' between them.

char	*rebuild_value(t_data *data, t_env *current)
{
	char	*temp;
	char	*rebuild_value;

	if (current->content == NULL)
	{
		rebuild_value = ft_strdup(current->name);
		data->saved_errno = errno;
		if (!rebuild_value)
			return (NULL);
		return (rebuild_value);
	}
	temp = ft_strjoin(current->name, "=");
	data->saved_errno = errno;
	if (!temp)
		return (NULL);	
	rebuild_value = ft_strjoin(temp, current->content);
	data->saved_errno = errno;
	ft_free((void **)&temp);
	if (!rebuild_value)
		return (NULL);
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
	char	**converted_env;
	int		y;

	y = 0;
	current = env;
	while (current != NULL)
	{
		current = current->next;
		y++;
	}
	converted_env = ft_calloc(y + 1, sizeof(char *));
	data->saved_errno = errno;
	if (!converted_env)
		ft_error_child(data, MALLOC_ERR, 1);
	current = env;
	y = 0;
	while (current != NULL)
	{
		converted_env[y] = rebuild_value(data, current);
		if (!converted_env)
		{
			ft_free_tab(&converted_env);
			ft_error_child(data, MALLOC_ERR, 1);
		}
		current = current->next;
		y++;
	}
	return (converted_env);
}
