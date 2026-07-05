#include "../minishell_general.h"

int	ft_error_parent_int(t_data *data, t_bool do_i_perror, char *message, int code)
{
	if (code != 0 && do_i_perror == B_TRUE)
		perror(message);
	data->code = code;
	return (1);
}

char	*ft_error_parent(t_data *data, t_bool do_i_perror, char *message, int code)
{
	if (code != 0 && do_i_perror == B_TRUE)
		perror(message);
	data->code = code;
	return (NULL);
}

void	ft_error_child(t_data *data, t_bool do_i_perror, char *message,
		int code)
{
	char	*ptr;

	if (code != 0 && do_i_perror == B_TRUE)
		perror(message);
	free_and_close_life(data);
	if (data->cmd_data != NULL)
		free_cmd_data(data->cmd_data);
	exit(code);
}
