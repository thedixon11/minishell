/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:23:24 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:23:25 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

void	create_env(char **envp, t_data *data)
{
	int		x;
	t_env	*node;

	x = 0;
	while (envp[x] != NULL)
	{
		node = new_node_env(envp[x], data);
		add_node_env(node, data);
		x++;
	}
}

void	add_node_env(t_env *current, t_data *data)
{
	t_env	*temp;

	if (data->env == NULL)
		data->env = current;
	else
	{
		temp = data->env;
		while (temp->next != NULL)
			temp = temp->next;
		current->next = NULL;
		current->prev = temp;
		temp->next = current;
	}
}

t_env	*new_node_env(char *line, t_data *data)
{
	t_env	*node;
	char	*equal;

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		error_int(data, I_CALLOC, LIBFT_ERR, 1);
	equal = ft_strchr(line, '=');
	node->name = ft_substr(line, 0, equal - line);
	if (!node->name)
	{
		ft_free((void **)&node);
		error_int(data, I_SUBSTR, LIBFT_ERR, 1);
	}
	node->content = strdup(equal + 1);
	if (!node->content)
	{
		ft_free((void **)&node->name);
		ft_free((void **)&node);
		error_int(data, I_STRDUP, LIBFT_ERR, 1);
	}
	return (node);
}
