#include "../minishell_general.h"
#include "minishell_builtin.h"

int	add_quotes_content(t_data *data, char ***c_env)
{
	int		y;
	char	*temp1;
	char	*temp2;
	char	*temp3;

	y = 0;
	while (c_env[0][y] != NULL)
	{
		temp1 = get_name_var_env(data, c_env[0][y]);
		temp2 = get_content_var_env(data, c_env[0][y]);
		if (temp2 != NULL)
		{
			temp3 = ft_strsrrnd(temp2, "\"");
			ft_free((void **)&temp2);
			temp2 = ft_strjoin("=", temp3);
			ft_free((void **) &temp3);
			temp3 = ft_strjoin(temp1, temp2);
			ft_free((void **)&c_env[0][y]);
			c_env[0][y] = temp3;
		}
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
		ft_putendl_fd(env[y], STDIN_FILENO);
		y++;
	}
}

void	export_no_args(t_data *data)
{
	int		i;
	int		j;
	int		size;
	char	**c_env;

	i = 0;
	j = 1;
	size = 0;
	c_env = env_converter_ll_to_array(data, data->env);
	add_quotes_content(data, &c_env);
	while (c_env[i] != NULL)
	{
		j = i + 1;
		size = ft_strlen(c_env[i]) + 1;
		while (c_env[j] != NULL && ft_strncmp(c_env[i], c_env[j], size) <= 0)
			j++;
		if (c_env[j] != NULL && ft_strncmp(c_env[i], c_env[j], size) > 0)
			swap_values(&c_env, &i, j);
		else
			i++;
	}
	print_environment(c_env);
	ft_free_tab(&c_env);
}
