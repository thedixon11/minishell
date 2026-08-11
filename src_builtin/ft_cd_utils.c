#include "../minishell_general.h"

int	ft_cd_error(t_data *data, char *path, char *message, int code)
{
	write(2, "minishell: cd: ", 15);
	write(2, path, ft_strlen(path));
	write(2, ": ", 2);
	write(2, message, ft_strlen(message));
	write(1, "\n", 1);	
	data->saved_errno = 0;
	data->error = 0;
	data->code = code;
	return (1);
}
