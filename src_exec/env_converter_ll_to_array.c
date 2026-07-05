#include "../minishell_general.h"
#include "minishell_xecution.h"

// NOTE: rebuld_value have the mission to fusion name of all env_var with their
// respective content and '=' between them.

char	*rebuild_value(t_data *data, t_env *current)
{
	char	*temp;
	char	*rebuild_value;

	temp = ft_strjoin(current->name, "=");
	data->saved_errno = errno;
	if (!temp)
		ft_error_child(data, B_TRUE, MALLOC_ERR, 1);
	rebuild_value = ft_strjoin(temp, current->content);
	data->saved_errno = errno;
	ft_free((void**)&temp);
	if (!rebuild_value)
		ft_error_child(data, B_TRUE, MALLOC_ERR, 1);
	return (rebuild_value);
}

// NOTE: before executing the command, it's necessary to convert the
// environment from linked list to array, because execve need it in this
// format. That's the job of env_converter_ll_to_array. To do that,
// we need:
// 1) count how many env_var exists in the environment;
// 2) have to rebuild the values
// (we have to join name, '=' and content together)

void	env_converter_ll_to_array(t_data *data, t_env *env)
{
	t_env	*current;
	int		y;

	y = 0;
	current = env;
	while (current != NULL)
	{
		current = current->next;
		y++;
	}
	data->cmd_data->env = ft_calloc(y + 1, sizeof(char *));
	data->saved_errno = errno;
	if (!data->cmd_data->env)
		ft_error_child(data, B_TRUE, MALLOC_ERR, 1);
	current = env;
	y = 0;
	while (current != NULL)
	{
		data->cmd_data->env[y] = rebuild_value(data, current);
		current = current->next;
		y++;
	}
}
