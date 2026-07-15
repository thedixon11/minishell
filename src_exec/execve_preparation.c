#include "../minishell_general.h"
#include "minishell_xecution.h"

void	check_cmd_is_not_empty(t_data *data, t_line *current)
{
	if (current->content_xpand == NULL)
	{
		free_and_close_life(data);
		exit(0);
	}
	if (current->content_xpand[0][0] == 0)
	{
		if (ft_strchr(current->content, '"') != 0)
			ft_error_child_cmd_not_found(data, "", 1);
	}
}

// NOTE: here we check if the programm exists and is executable
// with the function access

int	is_prog_existing_and_executable(t_data *data, char *path_to_check)
{
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

char	**find_path_tab(t_data *data)
{
	t_env	*current;
	char	**path_tab;

	current = data->env;
	while (current != NULL)
	{
		if (ft_strncmp(current->name, "PATH", 5) == 0)
			path_tab = create_path_tab(data, current->content);
		current = current->next;
	}
	return (path_tab);
}
