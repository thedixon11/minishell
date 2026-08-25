/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_there_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:14:22 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:14:23 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

int	create_new_env(t_data *data)
{
	create_pwd_value(data);
	create_shlvl_value(data);
	return (0);
}

t_bool	check_if_value_exist(t_data *data, char *value)
{
	t_env	*current;
	int		len;

	current = data->env;
	len = ft_strlen(value) + 1;
	while (current != NULL)
	{
		if (ft_strncmp(current->name, value, len) == 0)
			return (B_TRUE);
		current = current->next;
	}
	return (B_FALSE);
}

int	initialize_env(t_data *data, char **envp)
{
	if (envp == NULL || envp[0] == NULL)
		return (create_new_env(data));
	else
	{
		create_env(envp, data);
		if (check_if_value_exist(data, "PWD") == B_FALSE)
			create_pwd_value(data);
		else
			update_pwd_value(data);
		if (check_if_value_exist(data, "SHLVL") == B_FALSE)
			create_shlvl_value(data);
		else
			update_shlvl_value(data);
	}
	return (0);
}
