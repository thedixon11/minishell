#include "../minishell_general.h"

void	print_var_error(char *identifier)
{
	ft_printf("%s : not a valid identifier\n", identifier);
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
		return (NULL);
	start++;
	end = start;
	while (name_n_value[end] != 0)
		end++;
	content = ft_substr(name_n_value, start, end - start);
	data->saved_errno = errno;
	if (!content)
		ft_error_parent_char(data, MALLOC_ERR, 1);
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
	data->saved_errno = errno;
	if (!name)
		ft_error_parent_char(data, MALLOC_ERR, 1);
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

t_bool	check_var_env_name(char	*name)
{
	int	i;

	i = 1;
	if (name[0] != '_' && ft_isalpha(name[0]) != 1)
		return (B_FALSE);
	while (name[i] != 0)
	{
		if (name[i] != '_' && ft_isalnum(name[i]) != 1)
			return (B_FALSE);
		i++;
	}
	return (B_TRUE);
}
