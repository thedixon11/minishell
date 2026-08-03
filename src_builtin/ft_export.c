#include "../minishell_general.h"
#include "minishell_builtin.h"

int	create_new_var_env(t_data *data, char *name, char *content)
{
	t_env	*current;
	t_env	*new_var_env;

	new_var_env = ft_calloc(1, sizeof(t_env));
	if (!new_var_env)
		return (error_int(data, I_EXPORT, LIBFT_ERR, 1));
	new_var_env->name = ft_strdup(name);
	if (!new_var_env->name)
		return (ft_free((void **)&new_var_env), error_int(data, I_EXPORT, LIBFT_ERR, 1));
	new_var_env->content = ft_strdup(content);
	if (!new_var_env->content)
		return (ft_free((void **)&new_var_env->name), ft_free((void **)&new_var_env),
				error_int(data, I_EXPORT, LIBFT_ERR, 1));
	current = data->env;
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
	if (!current->content)
		return (error_int(data, I_EXPORT, LIBFT_ERR, 1));
	return (0);
}

t_env	*does_var_env_exist(t_data *data, char *name)
{
	int		len;
	t_env	*current;

	current = data->env;
	len = ft_strlen(name) + 1;
	while (current != NULL)
	{
		if (ft_strncmp(current->name, name, len) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

int	repl_create_var(t_data *data, char *name, char *content)
{
	t_env	*current;

	current = does_var_env_exist(data, name);
	if (current != NULL && content[0] != 0)
		return (replace_content_value(data, current, content));
	else if (current != NULL && content[0] == 0)
		return (0);
	else
		return (create_new_var_env(data, name, content));
}

int	ft_export(t_data *data, char **cmd_args)
{
	int		y;
	char	*name;
	char	*content;

	y = 1;
	if (how_much_args(cmd_args) == 1)
		return (export_no_args(data));
	while (cmd_args[y] != NULL)
	{
		name = get_name_var_env(data, cmd_args[y]);
		if (!name)
			return(1);
		if (check_var_env_name(data, &name, cmd_args[y], &y) == B_FALSE)
			continue ;
		content = get_content_var_env(data, cmd_args[y]);
		if (!content)
			return (ft_free((void **)&name), 1);
		if (repl_create_var(data, name, content) == 1)
			return (ft_free((void **)&name), ft_free((void **)&content), 1);
		ft_free((void **)&name);
		ft_free((void **)&content);
		y++;
	}
	export_no_args(data);	// NOTE: juste pour voir le resultat directement (test)
	return (0);
}
