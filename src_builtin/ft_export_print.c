#include "../minishell_general.h"
#include "minishell_builtin.h"

char	*add_quotes_content_util(t_data *data, char **name, char **content)
{
	char	*result;

	result = ft_strsrrnd(*content, "\"");
	ft_free((void **)content);
	if (!result)
		return (ft_free((void **)name),
			error_char(data, I_EXPORT, LIBFT_ERR, 1));
	*content = ft_strjoin("=", result);
	ft_free((void **) &result);
	if (!*content)
		return (ft_free((void **)name),
			error_char(data, I_EXPORT, LIBFT_ERR, 1));
	result = ft_strjoin(*name, *content);
	ft_free((void **)content);
	ft_free((void **)name);
	if (!result)
		return (error_char(data, I_EXPORT, LIBFT_ERR, 1));
	return (result);
}

int	add_quotes_content(t_data *data, char ***c_env)
{
	int		y;
	char	*name;
	char	*content;

	y = 0;
	while (c_env[0][y] != NULL)
	{
		name = get_name_var_env(data, c_env[0][y]);
		if (!name)
			return (1);
		content = get_content_var_env(data, c_env[0][y]);
		if (!content)
			return (1);
		if (content[0] != 0)
		{
			ft_free((void **)&c_env[0][y]);
			c_env[0][y] = add_quotes_content_util(data, &name, &content);
			if (!c_env[0][y])
				return (1);
		}
		ft_free((void **)&content);
		ft_free((void **)&name);
		y++;
	}
	return (0);
}

void	swap_values(char ***env, int *i, int j)
{
	char	*temp;

	temp = env[0][*i];
	env[0][*i] = env[0][j];
	env[0][j] = temp;
	*i = 0;
}

void	print_environment(char **env)
{
	int	y;

	y = 0;
	while (env[y] != NULL)
	{
		ft_putendl_fd(env[y], 1);
		y++;
	}
}

void	sort_env_tab(char ***c_env)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 1;
	size = 0;

	while (c_env[0][i] != NULL)
	{
		j = i + 1;
		size = ft_strlen(c_env[0][i]) + 1;
		while (c_env[0][j] != NULL &&
			ft_strncmp(c_env[0][i], c_env[0][j], size) <= 0)
			j++;
		if (c_env[0][j] != NULL &&
			ft_strncmp(c_env[0][i], c_env[0][j], size) > 0)
			swap_values(c_env, &i, j);
		else
			i++;
	}
}

int	export_no_args(t_data *data)
{
	char	**c_env;

	c_env = env_converter_ll_to_array(data, data->env);
	if (!c_env)
		return (1);
	if (add_quotes_content(data, &c_env) == 1)
		return (ft_free_tab(&c_env), 1);
	sort_env_tab(&c_env);
	print_environment(c_env);
	ft_free_tab(&c_env);
	return (0);
}
