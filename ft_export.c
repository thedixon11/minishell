
int	create_new_var_env(t_data *data, t_env *env, char *name, char *content)
{
	t_env	*current;
	t_env	*new_var_env;

	new_var_env = ft_calloc(1, sizeof(t_env *));
	new_var_env->name = ft_strdup(name);
	data->errno = errno;
	if (!new_var_env->name)
		return (ft_error_parent_int());
	new_var->env->content = ft_strdup(content);
	data->errno = errno;
	if (!new_var_env->content)
		return (ft_free(&new_var_env->name), ft_error_parent_int());
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
	ft_free(current->content);
	current->content = ft_strdup(content);
	data->errno = errno;
	if (!current->content)
		return (ft_error_parent_int());
	return (0);
}

t_env	*does_var_env_exist(t_data *data, t_env *env, char *name)
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

t_bool	check_var_env_name(char	*name)
{
	int	i;

	i = 1;
	if (name[0] != '_' || ft_isalpha(name[0]) != 1)
		return (B_FALSE);
	while (name[i] != 0)
	{
		if (name[i] != '_' || ft_isalnum(name[i]) != 1)
			return (B_FALSE);
		i++;
	}
	return (B_TRUE);
}

int how_much_args(char **cmd_args)
{
	int	y;

	y = 1;
	while (cmd_args[y] != NULL)
		y++;
	return (y);
}


void	ft_export(t_data *data, t_env *env, char **cmd_args)
{
	t_env	*current;
	int	y;
	char	*name;
	char	*content

	y = 1;
	if (how_much_args(data, env, cmd_args) == 1)
		print_env_in_order(data, env, cmd_args);
	while (current != NULL)
	{
		name = get_name_var_env(cmd_args[y]);
		if (ft_strchr(cmd_args[y], '=') != NULL)
			content = get_content_var_name(cmd_args[y]);
		else
			content = NULL;
		if (check_var_env_name(name == B_FALSE))
			print_var_env_error(name);
		current = does_var_env_exist(data, env, name);
		if (current != NULL)
			replace_content_value(data, content, current);
		else
			create_new_var_env(data, env, name, content);

		y++;
	}
}
