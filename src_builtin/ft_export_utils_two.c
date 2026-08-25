/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils_two.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:10:06 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:10:09 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

t_env	*create_new_node_env(t_data *data, char *name, char *content)
{
	t_env	*new_var_env;

	new_var_env = ft_calloc(1, sizeof(t_env));
	if (!new_var_env)
		return (error_int(data, I_EXPORT, LIBFT_ERR, 1), NULL);
	new_var_env->name = ft_strdup(name);
	if (!new_var_env->name)
		return (ft_free((void **)&new_var_env), error_int(data, I_EXPORT,
				LIBFT_ERR, 1), NULL);
	new_var_env->content = ft_strdup(content);
	if (!new_var_env->content)
		return (ft_free((void **)&new_var_env->name),
			ft_free((void **)&new_var_env), error_int(data, I_EXPORT, LIBFT_ERR,
				1), NULL);
	return (new_var_env);
}

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
