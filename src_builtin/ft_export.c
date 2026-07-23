#include "../minishell_general.h"
#include "minishell_builtin.h"

int	create_new_var_env(t_data *data, t_env *env, char *name, char *content)
{
	t_env	*current;
	t_env	*new_var_env;

	new_var_env = ft_calloc(1, sizeof(t_env *));
	if (name != NULL)
	{
		new_var_env->name = ft_strdup(name);
		data->saved_errno = errno;
		if (!new_var_env->name)
			return (ft_error_parent_int(data, MALLOC_ERR, 1));
	}
	if (content != NULL)
	{
		new_var_env->content = ft_strdup(content);
		data->saved_errno = errno;
		if (!new_var_env->content)
			return (ft_free((void **)&new_var_env->name), ft_error_parent_int(data, MALLOC_ERR, 1));
	}
	current = env;
	while (current->next != NULL)
		current = current->next;
	current->next = new_var_env;
	new_var_env->prev = current;
	new_var_env->next = NULL;
	return (0);
}

int	replace_content_value(t_data *data, t_env *current, char *content)
{
	if (content == NULL)
		return (0);
	ft_free((void **)&current->content);
	current->content = ft_strdup(content);
	data->saved_errno = errno;
	if (!current->content)
		return (ft_error_parent_int(data, MALLOC_ERR, 1));
	return (0);
}

t_env	*does_var_env_exist(t_env *env, char *name)
{
	int	len;
	t_env	*current;

	current = env;
	len = ft_strlen(name) + 1;
	while (current != NULL)
	{
		if (ft_strncmp(current->name, name, len) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	ft_export(t_data *data, t_env *env, char **cmd_args)
{
	t_env	*current;
	int	y;
	char	*name;
	char	*content;
	char	**c_env;


	y = 1;
	current = NULL;
	if (how_much_args(cmd_args) == 1)
		export_no_args(data, env);
	while (cmd_args[y] != NULL)
	{
		name = get_name_var_env(data, cmd_args[y]);
		content = get_content_var_env(data, cmd_args[y]);
		if (check_var_env_name(name) == B_FALSE)
			//print_var_env_error(name);
			return ;
		current = does_var_env_exist(env, name);
		if (current != NULL)
			replace_content_value(data, current, content);
		else
			create_new_var_env(data, env, name, content);
		y++;
	}
	c_env = env_converter_ll_to_array(data, env);
	print_environment(c_env);
}
