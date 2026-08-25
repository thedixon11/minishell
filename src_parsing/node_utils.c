/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:14:36 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:14:37 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

t_token	*new_token_node(t_data *data, char *value, t_type type)
{
	t_token	*current;

	current = ft_calloc(1, sizeof(t_token));
	if (!current)
		return (ft_free((void **)&value), error_token(data, I_CALLOC, LIBFT_ERR,
				1));
	current->value = ft_strdup(value);
	if (!current->value)
	{
		ft_free((void **)&current->value);
		ft_free((void **)&current);
		ft_free((void **)&value);
		return (error_token(data, I_STRDUP, LIBFT_ERR, 1));
	}
	current->type = type;
	current->next = NULL;
	current->prev = NULL;
	return (current);
}

void	add_token(t_data *data, t_token *current)
{
	t_token	*temp;

	if (data->token_head == NULL)
		data->token_head = current;
	else
	{
		temp = data->token_head;
		while (temp->next != NULL)
			temp = temp->next;
		current->next = NULL;
		current->prev = temp;
		temp->next = current;
	}
}
