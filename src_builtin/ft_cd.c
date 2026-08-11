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
			if (!current->content)
				return (error_int(data, I_STRDUP, LIBFT_ERR, 1));
		}
		else if (ft_strncmp(current->name, "OLDPWD", 7) == 0)
		{
			ft_free((void **)&current->content);
			current->content = ft_strdup(data->old_cwd);
			if (!current->content)
				return (error_int(data, I_STRDUP, LIBFT_ERR, 1));
		}
		current = current->next;
	}
	return (0);
}

int	update_data_wd(t_data *data, char *pathname)
{
	char	*temp_oldcwd;

	temp_oldcwd = getcwd(NULL, 0);
	if (!temp_oldcwd)
		error_int(data, I_CD, strerror(errno), 1);
	data->error = chdir(pathname);
	data->saved_errno = errno;
	if (data->error == -1)
		return (ft_free((void**)&temp_oldcwd), 
		  ft_cd_error(data, pathname, strerror(data->saved_errno), 1));
	ft_free((void **)&data->old_cwd);
	data->old_cwd = ft_strdup(temp_oldcwd);
	if (!data->old_cwd)
		return (ft_free((void**)&temp_oldcwd), error_int(data, I_CD, LIBFT_ERR, 1));
	ft_free((void **)&temp_oldcwd);
	ft_free((void **)&data->cwd);
	data->cwd = getcwd(NULL, 0);
	if (!data->cwd)
		return (error_int(data, I_CD, strerror(errno), 1));
	return (update_env_wd(data));
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
	return (error_int(data, I_CD, CD_NO_HOME, 1));
}

int	check_nb_args_cd(t_data *data, char **cmd_args)
{
	int	y;

	y = 0;
	while (cmd_args[y] != NULL)
		y++;
	if (y > 2)
		return (error_int(data, I_CD, CD_ARGS_ERR, 1));
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
