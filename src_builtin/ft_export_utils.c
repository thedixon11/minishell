#include "../minishell_general.h"

void	ft_export_error(t_data *data, char *identifier, int code)
{
	write(2, "minishell: export: ", 19);
	write(2, "\'", 1);
	write(2, identifier, ft_strlen(identifier));
	write(2, "\': ", 3);
	write(2, EXPORT_ID_ERR, ft_strlen(EXPORT_ID_ERR));
	write(1, "\n", 1);	
	data->saved_errno = 0;
	data->error = 0;
	data->code = code;
}

char	*get_content_var_env(t_data *data, char *name_n_value)
{
	int		start;
	int		end;
	char	*content;

	start = 0;
	while (name_n_value [start] != 0 && name_n_value[start] != '=')
		start++;
	if (name_n_value[start] == 0)
	{
		content = ft_strdup("");
		if (!content)
			return (error_char(data, I_EXPORT, LIBFT_ERR, 1));
		return (content);
	}
	start++;
	end = start;
	while (name_n_value[end] != 0)
		end++;
	content = ft_substr(name_n_value, start, end - start);
	if (!content)
		return (error_char(data, I_EXPORT, LIBFT_ERR, 1));
	return (content);
}

char	*get_name_var_env(t_data *data, char *name_n_value)
{
	int		len;
	char	*name;

	len = 0;
	while (name_n_value[len] != 0 && name_n_value[len] != '=')
		len++;
	name = ft_substr(name_n_value, 0, len);
	if (!name)
		return (error_char(data, I_EXPORT, LIBFT_ERR, 1));
	return (name);
}

int	how_much_args(char **cmd_args)
{
	int	y;

	y = 1;
	while (cmd_args[y] != NULL)
		y++;
	return (y);
}

t_bool	check_var_env_name(t_data *data, char **name, char *identifier, int *y)
{
	int	i;

	i = 1;
	if (name[0][0] != '_' && ft_isalpha(name[0][0]) != 1)
	{
		ft_export_error(data, identifier, 1);
		ft_free((void **)name);
		(*y)++;
		return (B_FALSE);
	}
	while (name[0][i] != 0)
	{
		if (name[0][i] != '_' && ft_isalnum(name[0][i]) != 1)
		{
			ft_export_error(data, identifier, 1);
			ft_free((void **)name);
			(*y)++;
			return (B_FALSE);
		}
		i++;
	}
	return (B_TRUE);
}
