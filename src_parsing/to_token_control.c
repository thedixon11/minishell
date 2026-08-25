/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_token_control.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:14:54 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:14:55 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

int	control_pipe_redir(t_data *data, t_token *current)
{
	if (current->prev == NULL || current->next == NULL)
		return (error_token_int(data, NULL, STAX_PIPE, 2));
	if (current->prev->type != T_COMMAND)
		return (error_token_int(data, NULL, STAX_PIPE, 2));
	if (current->next->type == T_PIPE)
		return (error_token_int(data, NULL, STAX_PIPE, 2));
	return (0);
}

int	control_classic_redir(t_data *data, t_token *current)
{
	if (current->next == NULL)
		return (error_token_int(data, NULL, STAX_NEWL, 2));
	if (operator_or_not(current->next) == B_TRUE)
	{
		if (current->next->type == T_HEREDOC)
			return (error_token_int(data, NULL, STAX_HDOC, 2));
		else if (current->next->type == T_INPUT)
			return (error_token_int(data, NULL, STAX_IN, 2));
		else if (current->next->type == T_OUTPUT_APPEND)
			return (error_token_int(data, NULL, STAX_OUT_APP, 2));
		else if (current->next->type == T_OUTPUT_TRUNC)
			return (error_token_int(data, NULL, STAX_OUT_TRNC, 2));
		else if (current->next->type == T_PIPE)
			return (error_token_int(data, NULL, STAX_PIPE, 2));
	}
	return (0);
}

int	control_the_operator(t_data *data, t_token *current)
{
	if (current->type == T_HEREDOC || current->type == T_INPUT)
		return (control_classic_redir(data, current));
	else if (current->type == T_OUTPUT_APPEND)
		return (control_classic_redir(data, current));
	else if (current->type == T_OUTPUT_TRUNC)
		return (control_classic_redir(data, current));
	else
		return (control_pipe_redir(data, current));
}

t_bool	operator_or_not(t_token *current)
{
	if (current->type == T_HEREDOC)
		return (B_TRUE);
	if (current->type == T_INPUT)
		return (B_TRUE);
	if (current->type == T_OUTPUT_APPEND)
		return (B_TRUE);
	if (current->type == T_OUTPUT_TRUNC)
		return (B_TRUE);
	if (current->type == T_PIPE)
		return (B_TRUE);
	return (B_FALSE);
}

int	control_token_line(t_data *data)
{
	t_token	*current;

	current = data->token_head;
	data->do_i_exit = B_FALSE;
	while (current != NULL)
	{
		if (operator_or_not(current) == B_TRUE)
		{
			if (control_the_operator(data, current) == 1)
			{
				data->do_i_exit = B_TRUE;
				return (1);
			}
		}
		current = current->next;
	}
	data->do_i_exit = B_TRUE;
	return (0);
}
