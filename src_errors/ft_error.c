#include "../minishell_general.h"

int	error_no_data(char *item, char *message, int code)
{
	write(2, "minishell: ", 11);
	write(2, item, ft_strlen(item));
	write(2, ": ", 2);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	return (code);
}

t_token	*error_token(t_state *state, char *message, int code, t_bool do_i_exit)
{
	write(2, "minishell: ", 11);	
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	free_state_data(state);
	if (do_i_exit == B_TRUE)
		exit (code);
	return (NULL);
}

int	error_int(t_data *data, char *item, char *message, int code)
{
	write(2, "minishell: ", 11);
	write(2, item, ft_strlen(item));
	write(2, ": ", 2);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	if (data->do_i_exit == B_TRUE)
	{
		free_and_close_life(data);
		exit (code);
	}
	data->saved_errno = 0;
	data->error = 0;
	data->code = code;
	return (1);
}

char	*error_char(t_data *data, char *item, char *message, int code)
{
	write(2, "minishell: ", 11);
	write(2, item, ft_strlen(item));
	write(2, ": ", 2);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	if (data->do_i_exit == B_TRUE)
	{
		free_and_close_life(data);
		exit (code);
	}
	data->saved_errno = 0;
	data->error = 0;
	data->code = code;
	return (NULL);
}
