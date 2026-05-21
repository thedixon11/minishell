#include "minishell_xecution.h"

t_data	*create_args_cmd(t_data *data, char *cmd)
{
	data->args_cmd = ft_split_squote(cmd, ' ');
	if (data->args_cmd == NULL)
		errors_exit(data, ARGC2_ERR, 0, 1);
	data->binary = ft_strdup(data->args_cmd[0]);
	if (data->binary == NULL)
		errors_exit(data, MALLOC_ERR, 0, 0);
	return (data);
}

int	is_binary_existing_and_executable(char *path_to_check)
{
	if (access(path_to_check, F_OK) != 0)
		return (-1);
	if (access(path_to_check, X_OK) != 0)
		return (-1);
	return (0);
}

t_data	*create_full_binary(t_data *data)
{
	size_t	y;
	char	*temp;

	y = 0;
	temp = ft_strjoin("/", data->binary);
	if (temp == NULL)
		errors_exit(data, MALLOC_ERR, 0, 0);
	while (data->path_tab[y] != NULL)
	{
		data->binary_full = ft_strjoin(data->path_tab[y], temp);
		if (data->binary_full == NULL)
			errors_exit(data, MALLOC_ERR, 0, 0);
		if (is_binary_existing_and_executable(data->binary_full) == 0)
		{
			free(temp);
			return (data);
		}
		free(data->binary_full);
		y++;
	}
	free(temp);
	data->binary_full = NULL;
	return (data);
}

t_data	*is_it_absolute_path(t_data *data)
{
	if (ft_strchr(data->binary, '/') == 0)
		return (data);
	if (is_binary_existing_and_executable(data->binary) == 0)
	{
		data->binary_full = ft_strdup(data->binary);
		if (data->binary_full == NULL)
			errors_exit(data, MALLOC_ERR, 0, 0);
		data->is_it_absolute_or_relative = 1;
	}
	else
	{
		free(data->binary);
		data->binary = NULL;
	}
	return (data);
}

t_data	*execve_preparation(t_data *data, int y, int error_num)
{
	data = create_args_cmd(data, data->argv[y]);
	data = is_it_absolute_path(data);
	if (data->binary == NULL)
		errors_exit(data, CMD_ERR, error_num, 1);
	data = create_path_env_var_tab(data);
	if (data->path_tab == NULL && data->is_it_absolute_or_relative == 0)
		errors_exit(data, CMD_ERR, error_num, 1);
	if (data->binary_full == NULL)
		data = create_full_binary(data);
	if (data->binary_full == NULL)
		errors_exit(data, CMD_ERR, error_num, 1);
	return (data);
}
