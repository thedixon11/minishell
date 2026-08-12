#include "../minishell_general.h"
#include "minishell_builtin.h"

void	echo_no_args(t_data *data)
{
	if (data->do_i_exit == B_TRUE)
	{
		free_env(&data->env);
		free_and_close_life(data);
		exit (0);
	}
}

t_bool	skip_option_n(t_data *data, char **args_cmd, int *y)
{
	int	x;

	x = 2;
	if (args_cmd[1] == NULL)
		echo_no_args(data);
	if (args_cmd[*y][0] != '-' || args_cmd[*y][1] != 'n')  // BUG:
		return (B_TRUE);
	while (args_cmd[*y][x] != 0 && args_cmd[*y][x] == 'n')
		x++;
	if (args_cmd[*y][x] != 0)
		return (B_TRUE);
	(*y)++;
	while (args_cmd[*y] != NULL)
	{
		x = 2;
		if (args_cmd[*y][0] != '-' && args_cmd[*y][1] != 'n')
			return (B_FALSE);
		while (args_cmd[*y][x] != 0 && args_cmd[*y][x] == 'n')
			x++;
		if (args_cmd[*y][x] != 0)
			return (B_FALSE);
		(*y)++;
	}
	return (B_FALSE);
}

int	ft_echo(t_data *data, char **args_cmd)
{
	int		y;
	t_bool	do_i_return;
	int		len;

	y = 1;
	len = 0;
	do_i_return = skip_option_n(data, args_cmd, &y);
	while (args_cmd[y] != NULL)
	{
		len = ft_strlen(args_cmd[y]);
		if (write(STDOUT_FILENO, args_cmd[y], len) == -1)
			return (error_int(data, I_ECHO, strerror(errno), 1));
		if (args_cmd[y + 1] == NULL && do_i_return == B_TRUE)
		{
			if (write(STDOUT_FILENO, "\n", 1) == -1)
				return (error_int(data, I_ECHO, strerror(errno), 1));
		}
		if (args_cmd[y + 1] != NULL)
		{
			if (write(STDOUT_FILENO, " ", 1) == -1)
				error_int(data, I_ECHO, strerror(errno), 1);
		}
		y++;
	}
	return (0);
}
