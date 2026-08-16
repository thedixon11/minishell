#include "../minishell_general.h"

void	join_path_prog(t_data *data, t_cmd *cmd_data, char *path,
		char *prog_name)
{
	char	*temp;

	temp = ft_strjoin("/", prog_name);
	if (!temp)
		error_int(data, I_STRJOIN, LIBFT_ERR, 1);
	cmd_data->prog_fullname = ft_strjoin(path, temp);
	ft_free((void **)&temp);
	if (!cmd_data->prog_fullname)
		error_int(data, I_STRJOIN, LIBFT_ERR, 1);
}

// NOTE: In the situation the programm can't be a relative/absolute,
// we'll check if it exists in the PATH or not. For that, we'll
// strjoin each directory of PATH with programm name, and check
// if it exists and is executable

void	check_prog_in_path(t_data *data, t_cmd *cmd_data, char *prog_name)
{
	size_t	y;

	y = 0;
	while (cmd_data->path_tab != NULL && cmd_data->path_tab[y] != NULL)
	{
		join_path_prog(data, cmd_data, cmd_data->path_tab[y], prog_name);
		if (is_prog_existing_and_executable(NULL, cmd_data) == 0)
			return ;
		ft_free((void **)&cmd_data->prog_fullname);
		y++;
	}
	ft_free((void **)&cmd_data->prog_fullname);
	error_int(data, prog_name, CMD_ERR, 127);
}

// NOTE: For the programm name, I have first to figure out if it could be
// an relative/absolute path or not, by strchr a '/'.
// Then I have to check if the programm exists and is executable or not
// (directly or by see if it's in the PATH)

void	prog_name_prep(t_data *data, t_cmd *cmd_data)
{
	t_line	*current;

	current = move_current_to_cmd(data);
	if (ft_strchr(cmd_data->args_tab[0], '/') == 0)
		check_prog_in_path(data, cmd_data, current->content_xpand[0]);
	else
	{
		cmd_data->prog_fullname = ft_strdup(cmd_data->args_tab[0]);
		if (!cmd_data->prog_fullname)
			error_int(data, I_STRDUP, LIBFT_ERR, 1);
	}
}
