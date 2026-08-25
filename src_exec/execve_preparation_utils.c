/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_preparation_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:12:25 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:21:07 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

void	join_path_prog(t_data *data, t_cmd *cmd_data, char *path,
		char *prog_name)
{
	char	*temp;

	temp = ft_strjoin("/", prog_name);
	if (!temp)
		error_int(data, I_STRJOIN, LIBFT_ERR, 1);
	cmd_data->prog_fullname = ft_strjoin(path, temp);
	ft_free((void **)&temp);
	if (!cmd_data->prog_fullname)
		error_int(data, I_STRJOIN, LIBFT_ERR, 1);
}

void	check_prog_in_path(t_data *data, t_cmd *cmd_data, char *prog_name)
{
	size_t	y;

	y = 0;
	while (cmd_data->path_tab != NULL && cmd_data->path_tab[y] != NULL)
	{
		join_path_prog(data, cmd_data, cmd_data->path_tab[y], prog_name);
		if (is_prog_existing_and_executable(NULL, cmd_data) == 0)
			return ;
		ft_free((void **)&cmd_data->prog_fullname);
		y++;
	}
	ft_free((void **)&cmd_data->prog_fullname);
	error_int(data, prog_name, CMD_ERR, 127);
}

void	prog_name_prep(t_data *data, t_cmd *cmd_data)
{
	t_line	*current;

	current = move_current_to_cmd(data);
	if (ft_strchr(cmd_data->args_tab[0], '/') == 0)
		check_prog_in_path(data, cmd_data, current->content_xpand[0]);
	else
	{
		cmd_data->prog_fullname = ft_strdup(cmd_data->args_tab[0]);
		if (!cmd_data->prog_fullname)
			error_int(data, I_STRDUP, LIBFT_ERR, 1);
	}
}
