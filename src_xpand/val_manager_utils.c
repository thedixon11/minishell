/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_manager_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:15:56 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:16:07 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

void	jump_quoted_content(char *content, int *end)
{
	char	quote;

	quote = content[*end];
	(*end)++;
	while (content[*end] != quote)
		(*end)++;
	(*end)++;
}

char	*go_until_dollar(t_data *data, char *content, int *start)
{
	int		end;
	char	*second;

	end = *start;
	second = NULL;
	while (content[end] != 0 && content[end] != '$')
	{
		while (content[end] != 0 && content[end] != '"' && content[end] != '\''
			&& content[end] != '$')
			end++;
		if (content[end] == '"' || content[end] == '\'')
			jump_quoted_content(content, &end);
	}
	second = ft_substr(content, *start, end - (*start));
	if (!second)
		return (error_char(data, I_SUBSTR, LIBFT_ERR, 1));
	*start = end;
	return (second);
}

char	*go_until_quote(t_data *data, char *content, int *start)
{
	int		end;
	char	*second;

	end = *start;
	second = NULL;
	while (content[end] != 0 && content[end] != '\'' && content[end] != '"')
		end++;
	second = ft_substr(content, *start, end - (*start));
	if (!second)
		return (error_char(data, I_SUBSTR, LIBFT_ERR, 1));
	*start = end;
	return (second);
}
