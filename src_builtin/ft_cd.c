#include "../minishell_general.h"

int	update_env_wd(t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current != NULL)
	{
		if (ft_strncmp(current->name, "PWD", 4) == 0)
		{
			ft_free((void **)&current->content);
			current->content = ft_strdup(data->cwd);
			data->saved_errno = errno;
			if (!current->content)
				return (ft_error_parent_int(data, MALLOC_ERR, 1));
		}
		else if (ft_strncmp(current->name, "OLDPWD", 7) == 0)
		{
			ft_free((void **)&current->content);
			current->content = ft_strdup(data->old_cwd);
			data->saved_errno = errno;
			if (!current->content)
				return (ft_error_parent_int(data, MALLOC_ERR, 1));
		}
		current = current->next;
	}
	return (0);
}

int	update_data_wd(t_data *data, char *pathname)
{
	char	*temp_oldcwd;

	temp_oldcwd = getcwd(NULL, 0);
	data->error = chdir(pathname);
	data->saved_errno = errno;
	if (data->error == -1)
		return (ft_free((void**)&temp_oldcwd), 
		  ft_error_parent_int(data, "not a directory", 2));	
	ft_free((void **)&data->old_cwd);
	data->old_cwd = ft_strdup(temp_oldcwd);
	data->saved_errno = errno;
	if (!data->old_cwd)
		return (ft_free((void**)&temp_oldcwd), ft_error_parent_int(data, MALLOC_ERR, 1));
	ft_free((void **)&data->cwd);
	data->cwd = ft_strdup(pathname);
	data->saved_errno = errno;
	if (!data->cwd)
		return (ft_error_parent_int(data, MALLOC_ERR, 1));
	update_env_wd(data);
	return (ft_free((void **)&temp_oldcwd), 0);
}

int	change_cwd_to_home(t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current != NULL)
	{
		if (ft_strncmp(current->name, "HOME", 5) == 0)
		{
			if (update_data_wd(data, current->content) != 0)
				return (1);
			return (0);
		}
		current = current->next;
	}
	return (ft_error_parent_int(data, "no HOME set up", 18));
}

int	check_nb_args_cd(t_data *data, char **cmd_args)
{
	int	y;

	y = 0;
	while (cmd_args[y] != NULL)
		y++;
	if (y > 2)
		return (ft_error_parent_int(data, "too much args bro in cd", 1));
	else if (y == 1)
		return (3);
	return (0);
}

int	ft_cd(t_data *data, char **cmd_args)
{
	if (check_nb_args_cd(data, cmd_args) == 1)
		return (1);
	else if (check_nb_args_cd(data, cmd_args) == 3)
		change_cwd_to_home(data);
	else
		update_data_wd(data, cmd_args[1]);
	return (0);
}
