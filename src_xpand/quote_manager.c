/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:15:50 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:16:54 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

char	*second_block_not_dollar(t_data *data, char *str, int *start)
{
	int		end;
	int		len;
	char	*second_block;

	end = *start;
	len = 0;
	second_block = NULL;
	while (str[end] != 0 && str[end] != '$')
		end++;
	len = end - *start;
	second_block = ft_substr(str, *start, len);
	if (!second_block)
		return (error_char(data, I_SUBSTR, LIBFT_ERR, 1));
	*start = end;
	return (second_block);
}

char	*quote_expansion(t_data *data, char *in_quote)
{
	char	*first;
	char	*second;
	int		i_quote;

	i_quote = 0;
	second = NULL;
	first = ft_strdup("");
	if (!first)
		return (error_char(data, I_STRDUP, LIBFT_ERR, 1));
	while (in_quote[i_quote] != 0)
	{
		if (in_quote[i_quote] != '$')
			second = second_block_not_dollar(data, in_quote, &i_quote);
		else if (in_quote[i_quote] == '$')
			second = dollar_manager(data, in_quote, &i_quote,
					Q_DOUBLE);
		if (second != NULL)
			first = fusion_first_second_block(data, first, second);
		else
			return (ft_free((void **)&first), NULL);
	}
	return (first);
}

char	*extract_quote(t_data *data, char *value, int *i_value, char quote)
{
	char	*inside_quote;
	int		end;
	int		len;

	(*i_value)++;
	end = *i_value;
	inside_quote = NULL;
	while (value[end] != quote)
		end++;
	len = end - *i_value;
	inside_quote = ft_substr(value, *i_value, len);
	*i_value = end + 1;
	if (!inside_quote)
		return (error_char(data, I_SUBSTR, LIBFT_ERR, 1));
	return (inside_quote);
}

char	*quote_manager(t_data *data, char *value, int *i_value, char quote)
{
	char	*inside_quote;
	char	*quote_result;

	inside_quote = NULL;
	quote_result = NULL;
	inside_quote = extract_quote(data, value, i_value, quote);
	if (!inside_quote)
		return (NULL);
	if (quote == '\'')
	{
		quote_result = ft_strdup(inside_quote);
		if (!quote_result)
			return (error_char(data, I_STRDUP, LIBFT_ERR, 1));
	}
	else if (quote == '\"')
		quote_result = quote_expansion(data, inside_quote);
	else
		return (ft_free((void **)&inside_quote), NULL);
	ft_free((void **)&inside_quote);
	if (!quote_result)
		return (NULL);
	return (quote_result);
}
