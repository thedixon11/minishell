#include "../minishell_general.h"
#include "minishell_builtin.h"

int	ft_env(t_data *data, char **cmd_args)
{
	int	y;
	t_env	*current;

	y = 0;
	while (cmd_args[y] != NULL)
		y++;
	if (y > 1)
		return (error_int(data, I_ENV, ENV_ARGS_ERR, 1));
	current = data->env;
	while (current != NULL)
	{
		if (ft_printf("%s=", current->name) == -1);
			return (error_int(data, I_ENV, LIBFT_ERR, 1));
		if (ft_printf("%s\n", current->content) == -1);
			return (error_int(data, I_ENV, LIBFT_ERR, 1));
		current = current->next;
	}
	return (0);
}
