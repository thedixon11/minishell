#include "../minishell_general.h"

// NOTE: the function go_until_dollar will create a block from start until
// next dollar. It is an util of expand_off_quote. If there is quotes, it
// will skip the dollars inside and no expansions will be done inside quotes.

char	*go_until_dollar(t_data *data, char *content, int *start)
{
	int		end;
	char	quote;
	char	*second_block;

	end = *start;
	quote = 'a';
	while (content[end] != 0 && content[end] != '$')
	{
		while (content[end] != 0 && content[end] != '"' && content[end] != '\''
			&& content[end] != '$')
			end++;
		if (content[end] == '"' || content[end] == '\'')
		{
			quote = content[end];
			end++;
			while (content[end] != quote)
				end++;
			end++;
		}
	}
	second_block = ft_substr(content, *start, end - (*start));
	data->saved_errno = errno;
	if (!second_block)
		return (ft_error_parent_char(data, B_TRUE, MALLOC_ERR, 1));
	*start = end;
	return (second_block);
}

// NOTE: the fonction go_until_quote will create a block from start
// until the next quote. It's an util of expand_in_quote function.

char	*go_until_quote(t_data *data, char *content, int *start)
{
	int		end;
	char	*second_block;

	end = *start;
	while (content[end] != 0 && content[end] != '\'' && content[end] != '"')
		end++;
	second_block = ft_substr(content, *start, end - (*start));
	data->saved_errno = errno;
	if (!second_block)
		return (ft_error_parent_char(data, B_TRUE, MALLOC_ERR, 1));
	*start = end;
	return (second_block);
}

// NOTE: Here is the third step to manage values.
// With expand_in_quote, we'll have to expend inside the quotes all the rows
// of splitted_content.
// We work in a system of first and second block. The idea is to manage the
// second block, either it is or not a dollar situation, and then to join
// the first block (already treated) with second block.
// This fusion becomes the new first block and we repeat the process.
//
// NOTE: the function go_until_quote will extract from i until the next
// entry quote.

char	*expand_in_quote(t_data *data, char *row)
{
	char	*first_block;
	char	*second_block;
	char	*temp;
	int		i;

	i = 0;
	first_block = ft_strdup("");
	data->saved_errno = errno;
	if (!first_block)
		return (ft_error_parent_char(data,B_TRUE, MALLOC_ERR, 1));
	while (row[i] != 0)
	{
		if (row[i] != '"' && row[i] != '\'')
			second_block = go_until_quote(data, row, &i);
		else if (row[i] == '"' || row[i] == '\'')
			second_block = quote_manager(data, row, &i, row[i]);
		if (second_block != NULL)
		{
			temp = first_block;
			first_block = ft_strjoin(temp, second_block);
			data->saved_errno = errno;
			ft_free((void**)&second_block);
			ft_free((void**)&temp);
			if (!first_block)
				return (ft_error_parent_char(data, B_TRUE, MALLOC_ERR, 1));
		}
		else
		{
			ft_free((void**)&first_block);
			return (NULL);
		}
	}
	return (first_block);
}

// NOTE: Here is the first step to manage values.
// With expand_off_quote, we'll expand all the content outside quotes.
// We work in a system of first and second block. The idea is to manage the
// second block, either it is or not a dollar situation, and then to join
// the first block (already treated) with second block.
// This fusion becomes the new first block and we repeat the process.
//
// NOTE: the function go_until_dollar will extract from i until the next
// dollar. The next dollar will be at this step outside a quote.

char	*expand_off_quote(t_data *data, char *content)
{
	char	*first_block;
	char	*second_block;
	char	*temp;
	int		i;

	i = 0;
	first_block = ft_strdup("");
	data->saved_errno = errno;
	if (!first_block)
		return (ft_error_parent_char(data, B_TRUE, MALLOC_ERR, 1));
	while (content[i] != 0)
	{
		if (content[i] != 0 && content[i] != '$')
			second_block = go_until_dollar(data, content, &i);
		else if (content[i] == '$')
			second_block = dollar_manager(data, content, &i, Q_NONE);
		if (second_block != NULL)
		{
			temp = first_block;
			first_block = ft_strjoin(temp, second_block);
			data->saved_errno = errno;
			ft_free((void**)&second_block);
			ft_free((void**)&temp);
			if (!first_block)
				return (ft_error_parent_char(data, B_TRUE, MALLOC_ERR, 1));
		}
		else
		{
			ft_free((void**)&first_block);
			return (NULL);
		}
	}
	return (first_block);
}

// NOTE: All contents of the nodes that are in the cmd linked list have to be
// manage with val_manager. For each content node, there is 3 steps :
//	1) we have to expand all content that is outside of quotes;
//	2) we have to split the content (spaces are the separators)
//	3) we have to expend inside quotes of all the lines of splitted_content;

int	val_manager(t_data *data)
{
	char	*temp;
	int		y;
	t_line	*current;

	y = 0;
	current = data->line_cmd;
	while (current != NULL)
	{
		y = 0;
		if (current->type == T_INPUT || current->type == T_OUTPUT_TRUNC
			|| current->type == T_OUTPUT_APPEND || current->type == T_COMMAND)
		{
			temp = expand_off_quote(data, current->content);
			if (!temp)
				return (1);
			current->content_xpand = ft_split(temp, ' ');
			data->saved_errno = errno;
			ft_free((void**)&temp);
			if (!current->content_xpand)
				return (ft_error_parent_int(data, B_TRUE, MALLOC_ERR, 1));
			while (current->content_xpand[y] != NULL)
			{
				temp = ft_strdup(current->content_xpand[y]);
				data->saved_errno = errno;
				if (!temp)
					return (ft_error_parent_int(data, B_TRUE, MALLOC_ERR, 1));
				ft_free((void**)&current->content_xpand[y]);
				current->content_xpand[y] = expand_in_quote(data, temp);
				ft_free((void**)&temp);
				if (!current->content_xpand[y])
					return (1);
				y++;
			}
		}
		current = current->next;
	}
	return (0);
}
