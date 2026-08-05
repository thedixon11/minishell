#include "../minishell_general.h"

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
			error_int(data, "", CMD_ERR, 1);
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

void	child_no_builtin(t_data *data)
{
	t_cmd	*cmd_data;

	data->do_i_exit = B_TRUE;
	cmd_data = ft_calloc(1, sizeof(t_cmd));
	if (!cmd_data)
		error_int(data, I_CALLOC, LIBFT_ERR, 1);
	data->cmd_data = cmd_data;
	create_args_tab(data, cmd_data);
	cmd_data->env = env_converter_ll_to_array(data, data->env);
	find_path_tab(data, cmd_data);
	if (cmd_data->args_tab != NULL)
		prog_name_prep(data, cmd_data);
	//is_prog_existing_and_executable(data, cmd_data);

	execve(cmd_data->prog_fullname, cmd_data->args_tab, cmd_data->env);
	error_int(data, I_EXECVE, strerror(errno), 1);
	free_and_close_life(data, B_TRUE);
	exit (1);
}

void	child_process(t_data *data)
{
	ft_close_fd(&data->saved_stdin);
	ft_close_fd(&data->saved_stdout);
	close_line_cmd_fds(data);
	close_line_cmd_fds_full(data);
	close_data_fds(data);
	if (is_it_builtin(data) == B_FALSE)
		child_no_builtin(data);
	else
		execute_builtin(data);
	free_and_close_life(data, B_TRUE);
	exit (0);
}

