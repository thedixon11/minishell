#include "../minishell_general.h"

char	*fusion_first_second_block(t_data *data, char *first, char *second)
{
	char	*temp;

	temp = first;
	first = ft_strjoin(temp, second);
	ft_free((void **)&second);
	ft_free((void **)&temp);
	if (!first)
		return (error_char(data, I_STRJOIN, LIBFT_ERR, 1));
	return (first);
}

// NOTE: will extract inside the quote

char	*extract_quote_hdoc(t_data *data, char *old_del, int *start, char quote)
{
	int		end;
	char	*inside_quote;

	(*start)++;
	end = *start;
	while (old_del[end] != quote)
		end++;
	inside_quote = ft_substr(old_del, *start, end - (*start));
	if (!inside_quote)
		return (error_char(data, I_SUBSTR, LIBFT_ERR, 1));
	*start = end + 1;
	return (inside_quote);
}

// NOTE: will extract before quote entry;

char	*go_until_quote_hdoc(t_data *data, char *old_del, int *start)
{
	int		end;
	char	*second_block;

	end = *start;
	while (old_del[end] != '\'' && old_del[end] != '"' && old_del[end] != 0)
		end++;
	second_block = ft_substr(old_del, *start, end - (*start));
	if (!second_block)
		return (error_char(data, I_SUBSTR, LIBFT_ERR, 1));
	*start = end;
	return (second_block);
}

// NOTE: go_until_dollar_hdoc will create a block until the
// next dollar. It's an util of expand_line_hdoc.

char	*go_until_dollar_hdoc(t_data *data, char *line, int *start)
{
	int		end;
	char	*second_block;

	end = *start;
	while (line[end] != 0 && line[end] != '$')
		end++;
	second_block = ft_substr(line, *start, end - (*start));
	if (!second_block)
		return (error_char(data, I_SUBSTR, LIBFT_ERR, 1));
	*start = end;
	return (second_block);
}

// NOTE: delimiter manager will treat the quotes of the delimiter and
// removed them

char	*delimiter_manager_hdoc(t_data *data, char *old_del)
{
	char	*first;
	char	*second;
	int		i;

	i = 0;
	first = ft_strdup("");
	if (!first)
		return (error_char(data, I_STRDUP, LIBFT_ERR, 1));
	while (old_del[i] != 0 && first != NULL)
	{
		if (old_del[i] != '\'' && old_del[i] != '\"' && old_del[i] != 0)
			second = go_until_quote_hdoc(data, old_del, &i);
		else if (old_del[i] == '\'' || old_del[i] != '\"')
			second = extract_quote_hdoc(data, old_del, &i, old_del[i]);
		if (second != NULL)
			first = fusion_first_second_block(data, first, second);
		else
		{
			ft_free((void **)&first);
			return (NULL);
		}
	}
	return (first);
}
