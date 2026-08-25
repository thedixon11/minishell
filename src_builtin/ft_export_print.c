#include "../minishell_general.h"
#include <unistd.h>

void	swap_values(char ***env, int *i, int j)
{
	char	*temp;

	temp = env[0][*i];
	env[0][*i] = env[0][j];
	env[0][j] = temp;
	*i = 0;
}

void	print_environment(t_data *data, char **env)
{
	int	y;

	y = 0;
	while (env[y] != NULL)
	{
		if (write(1, "declare -x ", 11) == -1)
		{
			ft_free_tab(&env);
			error_int(data, I_WRITE, LIBFT_ERR, 1);
		}
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
		while (c_env[0][j] != NULL && ft_strncmp(c_env[0][i], c_env[0][j],
			size) <= 0)
			j++;
		if (c_env[0][j] != NULL && ft_strncmp(c_env[0][i], c_env[0][j],
			size) > 0)
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
	print_environment(data, c_env);
	ft_free_tab(&c_env);
	return (0);
}
