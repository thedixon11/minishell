#include "../minishell_general.h"

void	swap_values(char ***env, int i, int j)
{
	char	*temp;

	temp = env[0][i];
	env[0][i] = env[0][j];
	env[0][j] = temp&;
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

void	export_no_args(t_data *data, t_env *env)
{
	int	i;
	int	j;
	int	size;
	char	**c_env;

	i = 0;
	j = 1;
	size = 0;
	c_env = env_converter_ll_to_array(data, env);
	while (c_env[i] != NULL)
	{
		j = i + 1;
		size = ft_strlen(c_env[i]) + 1;
		while (c_env[j] != NULL && ft_strncmp(c_env[i], c_env[j], size) <= 0)
			j++;
		if (c_env[j] != NULL && ft_strncmp(c_env[i], c_env[j], size) > 0)
		{
			swap_values(&c_env, i, j);
			i = 0;
		}
		else
			i++;
	}
	print_environment(c_env);
	ft_free_tab(&c_env);
}
