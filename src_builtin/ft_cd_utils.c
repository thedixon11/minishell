/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:09:26 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:09:27 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

int	ft_cd_error(t_data *data, char *path, char *message, int code)
{
	write(2, "minishell: cd: ", 15);
	write(2, path, ft_strlen(path));
	write(2, ": ", 2);
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	data->saved_errno = 0;
	data->error = 0;
	data->code = code;
	return (1);
}

char	*search_home_var(t_data *data)
{
	t_env	*current;

	current = data->env;
	while (current != NULL)
	{
		if (ft_strncmp(current->name, "HOME", 5) == 0)
			return (current->content);
		current = current->next;
	}
	return (NULL);
}

int	update_data_wd_home(t_data *data)
{
	char	*home_path;

	home_path = search_home_var(data);
	if (home_path == NULL)
		return (error_int(data, I_CD, CD_NO_HOME, 1));
	data->error = chdir(home_path);
	data->saved_errno = errno;
	if (data->error == -1)
		return (ft_cd_error(data, home_path, strerror(data->saved_errno), 1));
	ft_free((void **)&data->old_cwd);
	if (data->cwd != NULL)
		data->old_cwd = ft_strdup(data->cwd);
	else
		data->old_cwd = ft_strdup("");
	if (!data->old_cwd)
		return (error_int(data, I_CD, LIBFT_ERR, 1));
	ft_free((void **)&data->cwd);
	data->cwd = getcwd(NULL, 0);
	if (!data->cwd)
		return (error_int(data, I_CD, strerror(errno), 1));
	return (update_env_wd(data));
}
