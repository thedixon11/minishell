#include "../minishell_general.h"

// NOTE: the function go_until_dollar will create a block from start until
// next dollar. It is an util of expand_off_quote. If there is quotes, it
// will skip the dollars inside and no expansions will be done inside quotes.

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
	data->saved_errno = errno;
	if (!second)
		return (ft_error_parent_char(data, MALLOC_ERR, 1));
	*start = end;
	return (second);
}

// NOTE: the fonction go_until_quote will create a block from start
// until the next quote. It's an util of expand_in_quote function.

char	*go_until_quote(t_data *data, char *content, int *start)
{
	int		end;
	char	*second;

	end = *start;
	second = NULL;
	while (content[end] != 0 && content[end] != '\'' && content[end] != '"')
		end++;
	second = ft_substr(content, *start, end - (*start));
	data->saved_errno = errno;
	if (!second)
		return (ft_error_parent_char(data, MALLOC_ERR, 1));
	*start = end;
	return (second);
}
