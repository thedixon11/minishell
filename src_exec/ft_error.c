#include "../minishell_general.h"
#include "minishell_xecution.h"

int	ft_error_parent_int(t_data *data, t_bool do_i_perror, char *message, int code)
{
	char	*error_to_print;
	char	*temp1;
	char	*temp2;
	char	*temp3;

	if (code != 0 && do_i_perror == B_TRUE)
	{
		temp1 = ft_strjoin("minishell: ", message);
		temp2 = ft_strjoin(temp1, ": ");
		temp3 = ft_strdup(strerror(data->saved_errno));
		error_to_print = ft_strjoin(temp2, temp3);
		ft_free((void**)&temp1);
		ft_free((void**)&temp2);
		ft_free((void**)&temp3);
		ft_putendl_fd(error_to_print, STDERR_FILENO);	
		ft_free((void**)&error_to_print);
	}
	data->code = code;

	return (1);
}

char	*ft_error_parent_char(t_data *data, t_bool do_i_perror, char *message, int code)
{
	char	*error_to_print;
	char	*temp1;
	char	*temp2;
	char	*temp3;
	
	if (code != 0 && do_i_perror == B_TRUE)
	{
		temp1 = ft_strjoin("minishell: ", message);
		temp2 = ft_strjoin(temp1, ": ");
		temp3 = ft_strdup(strerror(data->saved_errno));
		error_to_print = ft_strjoin(temp2, temp3);
		ft_free((void**)&temp1);
		ft_free((void**)&temp2);
		ft_free((void**)&temp3);
		ft_putendl_fd(error_to_print, STDERR_FILENO);	
		ft_free((void**)&error_to_print);
	}
	data->code = code;
	return (NULL);
}

void	ft_error_child(t_data *data, t_bool do_i_perror, char *message,
		int code)
{
	char	*error_to_print;
	char	*temp1;
	char	*temp2;
	char	*temp3;

	if (code != 0 && do_i_perror == B_TRUE)
	{
		temp1 = ft_strjoin("minishell: ", message);
		temp2 = ft_strjoin(temp1, ": ");
		temp3 = ft_strdup(strerror(data->saved_errno));
		error_to_print = ft_strjoin(temp2, temp3);
		ft_free((void**)&temp1);
		ft_free((void**)&temp2);
		ft_free((void**)&temp3);
		ft_putendl_fd(error_to_print, STDERR_FILENO);	
		ft_free((void**)&error_to_print);
	}
	free_and_close_life(data);
	if (data->cmd_data != NULL)
		free_cmd_data(data->cmd_data);
	exit(code);
}
