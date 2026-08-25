/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_converter_ll_to_array.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:11:52 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:20:41 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

char	**initialize_converted_env(t_data *data, t_env *env)
{
	char	**converted_env;
	t_env	*current;
	int		i;

	i = 0;
	current = env;
	while (current != NULL)
	{
		i++;
		current = current->next;
	}
	converted_env = ft_calloc(i + 1, sizeof(char *));
	if (!converted_env)
		error_int(data, I_CALLOC, LIBFT_ERR, 1);
	return (converted_env);
}

char	*rebuild_value(t_data *data, t_env *current)
{
	char	*temp;
	char	*rebuild_value;

	temp = NULL;
	rebuild_value = NULL;
	if (current->content == NULL)
	{
		rebuild_value = ft_strdup(current->name);
		if (!rebuild_value)
			return (error_char(data, I_STRDUP, LIBFT_ERR, 1));
		return (rebuild_value);
	}
	temp = ft_strjoin(current->name, "=");
	if (!temp)
		return (error_char(data, I_STRJOIN, LIBFT_ERR, 1));
	rebuild_value = ft_strjoin(temp, current->content);
	ft_free((void **)&temp);
	if (!rebuild_value)
		return (error_char(data, I_STRJOIN, LIBFT_ERR, 1));
	return (rebuild_value);
}

char	**env_converter_ll_to_array(t_data *data, t_env *env)
{
	t_env	*current;
	char	**converted_env;
	int		y;

	current = env;
	converted_env = initialize_converted_env(data, env);
	if (!converted_env)
		return (NULL);
	current = env;
	y = 0;
	while (current != NULL)
	{
		converted_env[y] = rebuild_value(data, current);
		if (!converted_env)
		{
			ft_free_tab(&converted_env);
			break ;
		}
		current = current->next;
		y++;
	}
	return (converted_env);
}
