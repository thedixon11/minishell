#include "../minishell_general.h"

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
