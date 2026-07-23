#include "../minishell_general.h"

// NOTE: second_block_not_dollar_or_quote will create a block from i until
// the next dollar or quote (single or double). It's an utils for function
// quote_expansion.
//
// NOTE: str may be either value or inside_quote
// i may be either i_value or i_quote
//
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
	data->saved_errno = errno;
	if (!second_block)
		return (ft_error_parent_char(data, MALLOC_ERR, 1));
	*start = end;
	return (second_block);
}

// NOTE: In a double quote situation, we'll expand inside quotes with
// the function quote_expansion. We work in a system of first and second
// block. The idea is to manage the second block, either it is or not a dollar
// situation, and then to join the first block (already treated) with second
// block. This fusion becomes the new first block and we repeat the process.

char	*quote_expansion(t_data *data, char *in_quote)
{
	char	*first;
	char	*second;
	int		i_quote;

	i_quote = 0;
	second = NULL;
	first = ft_strdup("");
	data->saved_errno = errno;
	if (!first)
		return (ft_error_parent_char(data, MALLOC_ERR, 1));
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

// NOTE: with extract_quote, we'll extract from right after the entry quote,
// until the closing quote.

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
	data->saved_errno = errno;
	*i_value = end + 1;
	if (!inside_quote)
		return (ft_error_parent_char(data, MALLOC_ERR, 1));
	return (inside_quote);
}

// NOTE: quote_manager is the beginning to deal with what is inside quotes
// There is two steps:
//	1) we extract what's inside the quote;
//	2) if we are in double quotes situation, we'll expand the content.
//		Otherwise, we'll return the extracted inside quote content.
//
// NOTE: the value of *i is the location of the entry quote.
//
// WARNING: have to check if the else return NULL condition is useful
// or not

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
		data->saved_errno = errno;
		if (!quote_result)
			return (ft_error_parent_char(data, MALLOC_ERR, 1));
	}
	else if (quote == '\"')
		quote_result = quote_expansion(data, inside_quote);
	else
		return (NULL);
	ft_free((void **)&inside_quote);
	if (!quote_result)
		return (NULL);
	return (quote_result);
}
