#include "../minishell_general.h"

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



int	ft_error_parent_int(t_data *data, char *message, int code)
{
	char	*error_to_print;
	char	*temp1;
	char	*temp2;
	char	*temp3;

	temp1 = ft_strjoin("minishell: ", message);
	temp2 = ft_strjoin(temp1, ": ");
	temp3 = ft_strdup(strerror(data->saved_errno));
	error_to_print = ft_strjoin(temp2, temp3);
	ft_free((void **)&temp1);
	ft_free((void **)&temp2);
	ft_free((void **)&temp3);
	ft_putendl_fd(error_to_print, STDERR_FILENO);
	ft_free((void **)&error_to_print);
	data->saved_errno = 0;
	data->code = code;
	return (1);
}

char	*ft_error_parent_char(t_data *data, char *message, int code)
{
	char	*error_to_print;
	char	*temp1;
	char	*temp2;
	char	*temp3;

	temp1 = ft_strjoin("minishell: ", message);
	temp2 = ft_strjoin(temp1, ": ");
	temp3 = ft_strdup(strerror(data->saved_errno));
	error_to_print = ft_strjoin(temp2, temp3);
	ft_free((void **)&temp1);
	ft_free((void **)&temp2);
	ft_free((void **)&temp3);
	ft_putendl_fd(error_to_print, STDERR_FILENO);
	ft_free((void **)&error_to_print);
	data->saved_errno = 0;
	data->code = code;
	return (NULL);
}

int	ft_error_parent_amb_redir(t_data *data, char *message, int code)
{
	char	*temp1;
	char	*error_to_print;

	temp1 = ft_strjoin("minishell: ", message);
	ft_free((void **) &message);
	error_to_print = ft_strjoin(temp1, ": ambiguous redirection");
	ft_free((void **)&temp1);
	ft_putendl_fd(error_to_print, STDERR_FILENO);
	ft_free((void **)&error_to_print);
	data->saved_errno = 0;
	data->code = code;
	return (1);
}

void	ft_error_child_cmd_not_found(t_data *data, char *message, int code)
{
	char	*error_to_print;

	error_to_print = ft_strjoin(message, ": command not found");
	ft_putendl_fd(error_to_print, STDERR_FILENO);
	ft_free((void **)&error_to_print);
	free_cmd_data(data);
	free_and_close_life(data);
	exit(code);
}
void	ft_error_child(t_data *data, char *message, int code)
{
	char	*error_to_print;
	char	*temp1;
	char	*temp2;
	char	*temp3;

	temp1 = ft_strjoin("minishell: ", message);
	temp2 = ft_strjoin(temp1, ": ");
	temp3 = ft_strdup(strerror(data->saved_errno));
	error_to_print = ft_strjoin(temp2, temp3);
	ft_free((void **)&temp1);
	ft_free((void **)&temp2);
	ft_free((void **)&temp3);
	ft_putendl_fd(error_to_print, STDERR_FILENO);
	ft_free((void **)&error_to_print);
	free_cmd_data(data);
	free_and_close_life(data);
	exit(code);
}
