#include "../minishell_general.h"

int	create_new_env(t_data *data)
{
	create_pwd_value(data);
	create_shlvl_value(data);
	return (0);
}

int	update_shlvl_value(t_data *data)
{
	t_env	*current;
	int	shlvl_value;

	current = data->env;
	shlvl_value = 0;
	while (current != NULL)
	{
		if (ft_strncmp(current->name, "SHLVL", 6) == 0)
		{
			shlvl_value = ft_atoi(current->content) + 1;
			ft_free((void **)&current->content);
			current->content = ft_itoa(shlvl_value);
			if (current->content == NULL)
				error_int(data, I_ITOA, LIBFT_ERR, 1);
			return (0);
		}
		current = current->next;
	}
	return (1);
}

int	update_pwd_value(t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current != NULL)
	{
		if (ft_strncmp(current->name, "PWD", 4) == 0)
		{
			ft_free((void **)&current->content);
			current->content = getcwd(NULL, 0);
			if (current->content == NULL)
				error_int(data, I_GETCWD, strerror(errno), 1);
			return (0);
		}
		current = current->next;
	}
	return (1);
}

int	create_shlvl_value(t_data *data)
{
	t_env	*new_shlvl;

	new_shlvl = new_node_env("SHLVL=1");
	add_node_env(new_shlvl, &data->env);
	return (0);
}

int	create_pwd_value(t_data *data)
{
	char	*new_pwd_line;
	char	*temp;	
	t_env	*new_pwd;

	temp = getcwd(NULL, 0);
	if (!temp)
		error_int(data, I_GETCWD, strerror(errno), 1);
	new_pwd_line = ft_strjoin("PWD=", temp);
	ft_free((void **)&temp);
	if (!new_pwd_line)
		error_int(data, I_STRJOIN, LIBFT_ERR, 1);
	new_pwd = new_node_env(new_pwd_line);
	ft_free((void **)&new_pwd_line);
	add_node_env(new_pwd, &data->env);
	return (0);
}


t_bool	check_if_value_exist(t_data *data, char *value)
{
	t_env	*current;
	int	len;

	current = data->env;
	len = ft_strlen(value) + 1;
	while (current != NULL)
	{
		if (ft_strncmp(current->name, value, len) == 0)
			return (B_TRUE);
		current = current->next;
	}
	return (B_FALSE);
}

int	initialize_env(t_data *data, char **envp)
{
	if (envp == NULL || envp[0] == NULL)
		return (create_new_env(data));
	else
	{	data->env = create_env(envp);
		if (check_if_value_exist(data, "PWD") == B_FALSE)
			create_pwd_value(data);
		else
			update_pwd_value(data);
		if (check_if_value_exist(data, "SHLVL") == B_FALSE)
			create_shlvl_value(data);
		else
			update_shlvl_value(data);
	}
	return (0);
}
