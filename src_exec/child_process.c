#include "../minishell_general.h"
#include <string.h>
#include <sys/stat.h>

void	check_cmd_is_not_empty(t_data *data, t_line *current)
{
	if (current->content_xpand == NULL)
	{
		free_env(data->env);
		free_and_close_life(data);
		exit(0);
	}
	if (current->content_xpand[0][0] == 0)
	{
		if (ft_strchr(current->content, '"') != 0)
			error_int(data, "", CMD_ERR, 127);
	}
}

void	create_args_tab(t_data *data, t_cmd *cmd_data)
{
	t_line	*current;
	
	current = move_current_to_cmd(data);
	check_cmd_is_not_empty(data, current);
	cmd_data->args_tab = ft_arraydup(current->content_xpand);
	if (!cmd_data->args_tab)
    error_int(data, I_ARRAYDUP, LIBFT_ERR, 1);
}

int	is_directory(t_data *data, t_cmd *cmd_data)
{
	struct stat buf;

	if (stat(cmd_data->prog_fullname, &buf) == -1)
		error_int(data, cmd_data->prog_fullname, strerror(errno), 127);
	if (S_ISDIR(buf.st_mode))
		error_int(data, cmd_data->prog_fullname, DIR_ERR, 126);
	return (0);
}

void	child_no_builtin(t_data *data)
{
	t_cmd	*cmd_data;

	cmd_data = ft_calloc(1, sizeof(t_cmd));
	if (!cmd_data)
		error_int(data, I_CALLOC, LIBFT_ERR, 1);
	data->cmd_data = cmd_data;
	create_args_tab(data, cmd_data);
	cmd_data->env = env_converter_ll_to_array(data, data->env);
	find_path_tab(data, cmd_data);
	if (cmd_data->args_tab != NULL)
		prog_name_prep(data, cmd_data);
	is_directory(data, cmd_data);
	execve(cmd_data->prog_fullname, cmd_data->args_tab, cmd_data->env);
	error_int(data, I_EXECVE, strerror(errno), 1);
	free_and_close_life(data);
	exit (1);
}

void	child_process(t_data *data)
{
	data->do_i_exit = B_TRUE;
	ft_close_fd(&data->saved_stdin);
	ft_close_fd(&data->saved_stdout);
	close_line_cmd_fds(data);
	close_line_cmd_fds_full(data);
	close_data_fds(data);
	if (is_it_builtin(data) == B_FALSE)
		child_no_builtin(data);
	else
		execute_builtin(data);
	free_and_close_life(data);
	exit (0);
}

