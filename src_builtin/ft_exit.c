#include "../minishell_general.h"
#include "minishell_builtin.h"

int	ft_exit_error_int(t_data *data, char *arg, char *message, int code)
{
	write(2, "minishell: exit: ", 17);
	write(2, arg, ft_strlen(arg));
	write(2, ": ", 2);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	data->saved_errno = 0;
	data->error = 0;
	data->code = code;
	return (2);
}

int	ft_exit(t_data *data, char **cmd_args)
{
	int	x;
	int	y;
	int	exit_code;

	x = 0;
	y = 1;
	exit_code = data->code;
	if (ft_isdigit(cmd_args[1][x]) != 1)
	{
			ft_exit_error_int(data, cmd_args[1][x], EXIT_INVALID, 2);
			free_and_close_life(data);
			exit(2);
	}
	x++;
	while (cmd_args[y] != NULL)
		y++;
	if (y == 1)
		exit(exit_code);
	else if (y > 2)
		return (error_int(data, I_EXIT, EXIT_ARGS_ERR, 1));
	if (ft_atol(cmd_args[1]) > INT_MAX || ft_atol(cmd_args[1]) < INT_MIN)	
		exit(ft_exit_error_int(data, cmd_args[y], EXIT_INVALID, 2));
	exit_code = ft_atoi(cmd_args[1]) % 256;
	free_and_close_life(data);
	exit (exit_code);	
}
