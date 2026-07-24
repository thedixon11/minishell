#include "../minishell_general.h"
#include "minishell_builtin.h"

t_bool	skip_option_n(t_data *data, char **args_cmd, int *y)
{
	int	x;

	x = 2;
	if (args_cmd[*y][0] != '-' && args_cmd[*y][1] != 'n')
		return (B_FALSE);
	while (args_cmd[*y][x] != 0 && args_cmd[*y][x] == 'n')
		x++;
	if (args_cmd[*y][x] != 0)
		return (B_FALSE);
	(*y)++;
	while (args_cmd[*y] != NULL)
	{
		x = 2;
		if (args_cmd[*y][0] != '-' && args_cmd[*y][1] != 'n')
			return (B_TRUE);
		while (args_cmd[*y][x] != 0 && args_cmd[*y][x] == 'n')
			x++;
		if (args_cmd[*y][x] != 0)
			return (B_TRUE);
		(*y)++;
	}
	return (B_TRUE);
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
		data->error = write(STDOUT_FILENO, args_cmd[y], len);
		data->saved_errno = errno;
		if (data->error == -1)
			ft_error_child(data, WRITE_ERR, 1);
		if (args_cmd[y + 1] == NULL && do_i_return == B_TRUE)
		{
			data->error = write(STDOUT_FILENO, "\n", 1);	
			data->saved_errno = errno;
		}
		y++;
	}
	return (1);
}
