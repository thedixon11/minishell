/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_manager.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:15:32 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:17:22 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

char	*dollar_manager(t_data *data, char *str, int *i, t_quote q_mode)
{
	char	*result;

	if (q_mode == Q_NONE && (str[*i + 1] == '"' || str[*i + 1] == '\''))
		return (quote_after_dollar(data, i));
	else if (ft_isdigit(str[*i + 1]) == 1)
		return (digit_after_dollar(data, i));
	else if (str[*i + 1] == '?')
		return (dollar_is_error_code(data, i));
	else if (ft_isalpha(str[*i + 1]) == 1 || str[*i + 1] == '_')
	{
		result = env_var_manager(data, str, i);
		if (!result)
			return (NULL);
		return (result);
	}
	else if (str[*i + 1] == 0)
		return (zero_after_dollar(data, i));
	else
		return (dollar_not_alphanum_and_err(data, str, i));
}
