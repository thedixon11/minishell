#include "../minishell_general.h"
#include "minishell_builtin.h"

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
			ft_error_parent_int(data, "args should be only num please", 2);
			free_and_close_life(data);
			exit(2);
	}
	x++;
	while (cmd_args[y] != NULL)
		y++;
	if (y == 1)
		exit(exit_code);
	else if (y > 2)
		return (ft_error_parent_int(data, "too much args bro", 1));
	if (ft_atol(cmd_args[1]) > INT_MAX || ft_atol(cmd_args[1]) < INT_MIN)	
		exit(ft_error_parent_int(data, "args should be only num please", 2));
	exit_code = ft_atoi(cmd_args[1]) % 256;
	free_and_close_life(data);
	exit (exit_code);	
}
