#include "../minishell_general.h"
#include "minishell_xecution.h"

// NOTE: the function create_path_tab will split the PATH string that
// is in the environment, with ':' as separators and removing the
// "PATH=" at the beginning.

char	**create_path_tab(t_data *data, char *path_to_split)
{
	char	**path_tab;

	path_tab = ft_split(path_to_split, ':');
	data->saved_errno = errno;
	if (!path_tab)
		ft_error_child(data, MALLOC_ERR, 1);
	return (path_tab);
}

char	*join_path_prog(t_data *data, char *path, char *prog_name)
{
	char	*temp;
	char	*prog_fullname;

	temp = ft_strjoin("/", prog_name);
	data->saved_errno = errno;
	if (!temp)
		ft_error_child(data, MALLOC_ERR, 1);
	prog_fullname = ft_strjoin(path, temp);
	data->saved_errno = errno;
	ft_free((void **)&temp);
	if (!prog_fullname)
		ft_error_child(data, MALLOC_ERR, 1);
	return (prog_fullname);
}

// NOTE: In the situation the programm can't be a relative/absolute,
// we'll check if it exists in the PATH or not. For that, we'll
// strjoin each directory of PATH with programm name, and check
// if it exists and is executable

char	*check_prog_in_path(t_data *data, t_cmd *cmd_data, char *prog_name)
{
	size_t	y;
	char	*prog_fullname;

	y = 0;
	while (cmd_data->path_tab[y] != NULL)
	{
		prog_fullname = join_path_prog(data, cmd_data->path_tab[y], prog_name);
		if (is_prog_existing_and_executable(NULL, prog_fullname) == 0)
			return (prog_fullname);
		ft_free((void **)&prog_fullname);
		y++;
	}
	ft_free((void **)&prog_fullname);
	ft_error_child_cmd_not_found(data, prog_name, 127);
	return (NULL);
}

// NOTE: For the programm name, I have first to figure out if it could be
// an relative/absolute path or not, by strchr a '/'.
// Then I have to check if the programm exists and is executable or not
// (directly or by see if it's in the PATH)

char	*prog_name_prep(t_data *data, t_cmd *cmd_data, char **cmd_content)
{
	char	*prog_fullname;

	if (ft_strchr(cmd_data->args_tab[0], '/') == 0)
		prog_fullname = check_prog_in_path(data, cmd_data, cmd_content[0]);
	else
	{
		prog_fullname = ft_strdup(cmd_data->args_tab[0]);
		data->saved_errno = errno;
		if (!prog_fullname)
			ft_error_child(data, MALLOC_ERR, 1);
	}
	return (prog_fullname);
}
