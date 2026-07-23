#include "../minishell_general.h"

void	swap_values(char ***env, int i, int j)
{
	char	*temp;

	temp = env[0][i];
	env[0][i] = env[0][j];
	env[0][j] = temp;
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
	char	**env;

	i = 0;
	j = 1;
	size = 0;
	env_converter_ll_to_array(data, env);
	env = data->cmd_data->env;
	while (env[i] != NULL)
	{
		j = 0;
		size = ft_strlen(env[i]) + 1;
		while (env[j] != NULL && ft_strncmp(env[i], env[j], size) <= 0)
			j++;
		if (env[j] != NULL && ft_strncmp(env[i], env[j], size) > 0)
		{
			swap_values(&env, i, j);
			i = 0;
		}
		j = 0;
	}
	print_environment(env);
	ft_free_tab(&data->cmd_data->env);
}
