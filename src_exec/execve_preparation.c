#include "../minishell_general.h"

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
		ft_error_child(data, B_TRUE, "access not such file or directory", 1);
	}
	if (data != NULL && access(path_to_check, X_OK) != 0)
	{
		data->saved_errno = errno;
		ft_error_child(data, B_TRUE, "access not such file or directory", 127);
	}
	return (0);
}

// NOTE: the function create_path_array will split the PATH string that
// is in the environment, with ':' as separators and removing the
// "PATH=" at the beginning.

char	**create_path_array(t_data *data, char *path_to_split)
{
	char	**path_array;

	path_array = ft_split(path_to_split, ':');
	data->saved_errno = errno;
	if (!path_array)
		ft_error_child(data, B_TRUE, "malloc", 1);
	return (path_array);
}

// NOTE: In the situation the programm can't be a relative/absolute,
// we'll check if it exists in the PATH or not. For that, we'll
// strjoin each directory of PATH with programm name, and check
// if it exists and is executable

char	*create_prog_fullname(t_data *data, t_cmd *cmd_data, char *prog_name)
{
	size_t	y;
	char	*temp;
	char	*prog_fullname;

	y = 0;
	temp = ft_strjoin("/", prog_name);
	data->saved_errno = errno;
	if (!temp)
		ft_error_child(data, B_TRUE, "malloc", 1);
	while (cmd_data->path_array[y] != NULL)
	{
		prog_fullname = ft_strjoin(cmd_data->path_array[y], temp);
		data->saved_errno = errno;
		if (!prog_fullname)
			ft_error_child(data, B_TRUE, "malloc", 1);
		if (is_prog_existing_and_executable(data, prog_fullname) == 0)
		{
			ft_free((void**)&temp);
			return (prog_fullname);
		}
		ft_free((void**)&prog_fullname);
		y++;
	}
	ft_free((void**)&temp);
	ft_error_child(data, B_FALSE, "access command not found", 1);
	return (NULL);
}

// NOTE: Before executing the command, we have to prepare the material
// to use execve. For that, we need :
// a) complete programm name;
// b) array with args (is treated and created while expansion)
// c) array with all cmds path (original is in a str, have to convert it
//  to an array, and without the "PATH=");
// d) environment converted from linked list to array;
//
// NOTE: For the programm name, I have first to figure out if it could be
// an relative/absolute path or not, by strchr a '/'.
// Then I have to check if the programm exists and is executable or not
// (directly or by see if it's in the PATH)

t_cmd	*execve_preparation(t_data *data, char **cmd_content)
{
	t_cmd	*cmd_data;
	t_env	*current;

	current = data->env;
	cmd_data = ft_calloc(1, sizeof(t_cmd));
	data->saved_errno = errno;
	if (!cmd_data)
		ft_error_child(data, B_TRUE, "malloc", 1);
	data->cmd_data = cmd_data;
	cmd_data->args_array = ft_arraydup(cmd_content);
	data->saved_errno = errno;
	if (!cmd_data->args_array)
		ft_error_child(data, B_TRUE, "malloc", 1);
	cmd_data->env = env_converter_ll_to_array(data, data->env);
	while (current != NULL)
	{
		if (ft_strncmp(current->name, "PATH", 5) == 0)
			cmd_data->path_array = create_path_array(data, current->content);
		current = current->next;
	}
	if (ft_strchr(cmd_data->args_array[0], '/') == 0)
		cmd_data->prog_fullname = create_prog_fullname(data, cmd_data,
				cmd_content[0]);
	else
	{
		cmd_data->prog_fullname = ft_strdup(cmd_data->args_array[0]);
		data->saved_errno = errno;
		if (!cmd_data->prog_fullname)
			ft_error_child(data, B_TRUE, "malloc", 1);
	}
	if (is_prog_existing_and_executable(data, cmd_data->prog_fullname) != 0)
		return (NULL);
	return (cmd_data);
}
