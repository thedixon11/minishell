/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_preparation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:12:22 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:20:59 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

int	is_prog_existing_and_executable(t_data *data, t_cmd *cmd_data)
{
	char	*path_to_check;

	path_to_check = cmd_data->prog_fullname;
	if (data == NULL && access(path_to_check, F_OK) != 0)
		return (-1);
	if (data == NULL && access(path_to_check, X_OK) != 0)
		return (-1);
	if (data != NULL && access(path_to_check, F_OK) != 0)
		error_int(data, path_to_check, strerror(errno), 127);
	if (data != NULL && access(path_to_check, X_OK) != 0)
		error_int(data, path_to_check, strerror(errno), 126);
	return (0);
}

void	create_path_tab(t_data *data, t_cmd *cmd_data, char *path_to_split)
{
	cmd_data->path_tab = ft_split(path_to_split, ':');
	if (!cmd_data->path_tab)
		error_int(data, I_SPLIT, LIBFT_ERR, 1);
}

void	find_path_tab(t_data *data, t_cmd *cmd_data)
{
	t_env	*current;

	current = data->env;
	while (current != NULL)
	{
		if (ft_strncmp(current->name, "PATH", 5) == 0)
			create_path_tab(data, cmd_data, current->content);
		current = current->next;
	}
}
