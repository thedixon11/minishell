#include "../minishell_general.h"
#include "minishell_xecution.h"

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
		ft_error_child_amb_redir(data, path_to_check, 127);
	}
	return (0);
}

char	**find_path_array(t_data *data)
{
	t_env	*current;
	char	**path_array;

	current = data->env;
	while (current != NULL)
	{
		if (ft_strncmp(current->name, "PATH", 5) == 0)
			path_array = create_path_array(data, current->content);
		current = current->next;
	}
	return (path_array);
}

// NOTE: Before executing the command, we have to prepare the material
// to use execve. For that, we need :
// a) complete programm name;
// b) array with args (is treated and created while expansion)
// c) array with all cmds path (original is in a str, have to convert it
//  to an array, and without the "PATH=");
// d) environment converted from linked list to array;

t_cmd	*execve_preparation(t_data *data, char **cmd_content)
{
	t_cmd	*cmd_data;
	t_env	*current;

	current = data->env;
	cmd_data = ft_calloc(1, sizeof(t_cmd));
	data->saved_errno = errno;
	if (!cmd_data)
		ft_error_child(data, MALLOC_ERR, 1);
	data->cmd_data = cmd_data;
	cmd_data->args_array = ft_arraydup(cmd_content);
	data->saved_errno = errno;
	if (!cmd_data->args_array)
		ft_error_child(data, MALLOC_ERR, 1);
	env_converter_ll_to_array(data, data->env);
	cmd->data->path_array = find_path_array(data);
	cmd_data->prog_fullname = prog_name_prep(data, cmd_data, cmd_content);
	if (is_prog_existing_and_executable(data, cmd_data->prog_fullname) != 0)
		return (NULL);
	return (cmd_data);
}
