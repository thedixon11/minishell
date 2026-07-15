#include "../minishell_general.h"
#include "minishell_xecution.h"

void	free_child_process(char ***args_tab, char ***env, char ***path_tab, char **prog_fullname)
{
	ft_free_tab(args_tab);
	ft_free_tab(env);
	ft_free_tab(path_tab);
	ft_free((void **) prog_fullname);
}

char	**create_args_tab(t_data *data)
{
	t_line	*current;
	char	**args_tab;
	
	current = move_current_to_cmd(data);
	check_cmd_is_not_empty(data, current);
	args_tab = ft_arraydup(current->content_xpand);
	data->saved_errno = errno;
	if (!args_tab)
		ft_error_child(data, MALLOC_ERR, 1);
	return (args_tab);
}

void	child_process(t_data *data)
{
	char	**args_tab;
	char	**env;
	char	**path_tab;
	char	*prog_fullname;

	ft_close_fd(&data->saved_stdin);
	ft_close_fd(&data->saved_stdout);

	args_tab = create_args_tab(data);
	data->cmd_data.args_tab = args_tab;
	env = env_converter_ll_to_array(data, data->env);
	data->cmd_data.env = env;
	path_tab = find_path_tab(data);
	data->cmd_data.path_tab = path_tab;
	prog_fullname =	prog_name_prep(data, path_tab, args_tab);
	data->cmd_data.prog_fullname = prog_fullname;
	is_prog_existing_and_executable(data, prog_fullname);
	free_and_close_life(data);
	execve(prog_fullname, args_tab, env);
	data->saved_errno = errno;
	ft_error_child(data, EXECVE_ERR, 1);
}

