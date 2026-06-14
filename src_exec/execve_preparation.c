#include "minishell_xecution.h"

// NOTE: here we check if the programm exists and is executable
// with the function access

int	is_prog_existing_and_executable(char *path_to_check)
{
	if (access(path_to_check, F_OK) != 0)
		return (-1);
	if (access(path_to_check, X_OK) != 0)
		return (-1);
	return (0);
}

// NOTE: the function create_path_array will split the PATH string that
// is in the environment, with ':' as separators and removing the
// "PATH=" at the beginning.

char	**create_path_array(char *path_to_split)
{
	char  **path_array;

	path_array = ft_split(path_to_split, ':');
	if (!path_array)
  	exit(10);
	return (path_array);
}

// NOTE: In the situation the programm can't be a relative/absolute,
// we'll check if it exists in the PATH or not. For that, we'll
// strjoin each directory of PATH with programm name, and check
// if it exists and is executable

char	*create_prog_fullname(char **path_array, char *prog_name)
{
	size_t	y;
	char	*temp;
	char	*prog_fullname;

	y = 0;
	temp = ft_strjoin("/", prog_name);
	if (temp == NULL)
		exit(10);
	while (path_array[y] != NULL)
	{
		prog_fullname = ft_strjoin(path_array[y], temp);
		if (prog_fullname == NULL)
			exit(10);
		if (is_binary_existing_and_executable(prog_fullname) == 0)
		{
			free(temp);
			return (prog_fullname);
		}
		free(prog_fullname);
		y++;
	}
	free(temp);
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
	if (!cmd_data)
		return (NULL);
	cmd_data->args_array = cmd_content;
	cmd_data->env = env_converter_ll_to_array(data->env);
	while (current != NULL)
	{
		if (ft_strncmp(current->name, "PATH", 5) == 0)
			cmd_data->path_array = create_path_array(current->content);
		current = current->next;
	}
	if (ft_strchr(cmd_data->args_array[0], '/') == 0)
		cmd_data->prog_fullname = create_prog_fullname(cmd_data->path_array,
				cmd_content[0]);
	else
		cmd_data->prog_fullname = ft_strdup(cmd_data->args_array[0]);
	if (is_prog_existing_and_executable(cmd_data->prog_fullname) != 0)
		return (NULL);
	return (cmd_data);
}
