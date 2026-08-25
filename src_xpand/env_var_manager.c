/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:15:44 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:17:12 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

char	*env_var_checker(t_data *data, t_env *env, char *var_env)
{
	t_env	*current;
	int		len;
	char	*xpansion_result;

	len = ft_strlen(var_env) + 1;
	current = env;
	xpansion_result = NULL;
	while (current != NULL)
	{
		if (ft_strncmp(var_env, current->name, len) == 0)
		{
			xpansion_result = ft_strdup(current->content);
			if (!xpansion_result)
				return (error_char(data, I_STRDUP, LIBFT_ERR, 1));
			return (xpansion_result);
		}
		current = current->next;
	}
	xpansion_result = ft_strdup("");
	if (!xpansion_result)
		return (error_char(data, I_STRDUP, LIBFT_ERR, 1));
	return (xpansion_result);
}

char	*extract_env_var(t_data *data, char *str, int *i)
{
	int		end;
	int		len;
	char	*var_env;

	(*i)++;
	end = *i;
	len = 0;
	while (ft_isalnum(str[end]) == 1 || str[end] == '_')
		end++;
	len = end - *i;
	var_env = ft_substr(str, *i, len);
	if (!var_env)
		return (error_char(data, I_SUBSTR, LIBFT_ERR, 1));
	*i = end;
	return (var_env);
}

char	*env_var_manager(t_data *data, char *str, int *i)
{
	char	*xpansion_result;
	char	*var_env;

	var_env = extract_env_var(data, str, i);
	if (!var_env)
		return (NULL);
	xpansion_result = env_var_checker(data, data->env, var_env);
	ft_free((void **)&var_env);
	if (!xpansion_result)
		return (NULL);
	return (xpansion_result);
}
