/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_token_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:14:57 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:14:57 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

int	is_operator(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

t_type	get_type(t_state *state)
{
	if (state->str[state->i] == '|')
		return (T_PIPE);
	if (state->str[state->i] == '>' && state->str[state->i + 1] == '>')
		return (T_OUTPUT_APPEND);
	if (state->str[state->i] == '<' && state->str[state->i + 1] == '<')
		return (T_HEREDOC);
	if (state->str[state->i] == '<')
		return (T_INPUT);
	if (state->str[state->i] == '>')
		return (T_OUTPUT_TRUNC);
	return (T_COMMAND);
}
