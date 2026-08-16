#include "../minishell_general.h"

int	update_shlvl_value(t_data *data)
{
	t_env	*current;
	int		shlvl_value;

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
