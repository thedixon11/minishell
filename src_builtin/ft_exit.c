#include "../minishell_general.h"
#include "minishell_builtin.h"

int	ft_exit_error(t_data *data, char *arg, char *message, int code)
{
	write(2, "minishell: exit: ", 17);
	write(2, arg, ft_strlen(arg));
	write(2, ": ", 2);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
  data->do_i_exit = B_TRUE;
  free_and_close_life(data);
	return (code);
}

void  ft_exit_no_args(t_data *data, int exit_code)
{
  data->do_i_exit = B_TRUE;
  free_and_close_life(data);
  exit(exit_code);
}

t_bool	check_its_all_num(char *arg)
{
	int	x;

	x = 0;
	if (arg[x] == '+' || arg[x] == '-')
		x++;
	while (arg[x] != 0)
	{
		if (ft_isdigit(arg[x]) != 1)
			return (B_FALSE);
		x++;
	}
	return (B_TRUE);
}

int	ft_exit(t_data *data, char **cmd_args)
{
	int	y;
	int	exit_code;

	y = 1;
	exit_code = data->code;
	while (cmd_args[y] != NULL)
		y++;
	if (y == 1)
    ft_exit_no_args(data, exit_code);
	if (check_its_all_num(cmd_args[1]) == B_FALSE)
		exit(ft_exit_error(data, cmd_args[1], EXIT_INVALID, 2));
  if (ft_atol(cmd_args[1]) > INT_MAX || ft_atol(cmd_args[1]) < INT_MIN)	
		exit(ft_exit_error(data, cmd_args[y], EXIT_INVALID, 2));
	else if (y > 2)
		return (error_int(data, I_EXIT, EXIT_ARGS_ERR, 1));
	exit_code = ft_atoi(cmd_args[1]) % 256;
  data->do_i_exit = B_TRUE;
	free_and_close_life(data);
	exit (exit_code);	
}
