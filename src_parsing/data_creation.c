#include "../minishell_general.h"

static t_data	*data_creation(t_env *env, t_line *line_cmd)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);

	return (data);
}
