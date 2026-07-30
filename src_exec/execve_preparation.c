#include "../minishell_general.h"

// NOTE: here we check if the programm exists and is executable
// with the function access

int	is_prog_existing_and_executable(t_data *data, t_cmd *cmd_data)
{
	char	*path_to_check;

	path_to_check = cmd_data->prog_fullname;
	if (data == NULL && access(path_to_check, F_OK) != 0)
		return (-1);
	if (data == NULL && access(path_to_check, X_OK) != 0)
		return (-1);
	if (data != NULL && access(path_to_check, F_OK) != 0)
	{
		data->saved_errno = errno;
		ft_error_child_cmd_not_found(data, path_to_check, 12);
	}
	if (data != NULL && access(path_to_check, X_OK) != 0)
	{
		data->saved_errno = errno;
		ft_error_child_cmd_not_found(data, path_to_check, 12);
	}
	return (0);
}

// NOTE: the function create_path_tab will split the PATH string that
// is in the environment, with ':' as separators and removing the
// "PATH=" at the beginning.

void	create_path_tab(t_data *data, t_cmd *cmd_data, char *path_to_split)
{
	cmd_data->path_tab = ft_split(path_to_split, ':');
	if (!cmd_data->path_tab)
		error_libft_int(data, "ft_split", B_TRUE);
}

void	find_path_tab(t_data *data, t_cmd *cmd_data)
{
	t_env	*current;

	current = data->env;
	while (current != NULL)
	{
		if (ft_strncmp(current->name, "PATH", 5) == 0)
			create_path_tab(data, cmd_data, current->content);
		current = current->next;
	}
}
