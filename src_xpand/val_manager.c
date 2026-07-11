#include "../minishell_general.h"

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
	char	*first;
	char	*second;
	int		i;

	i = 0;
	second = NULL;
	first = ft_strdup("");
	data->saved_errno = errno;
	if (!first)
		return (ft_error_parent_char(data, MALLOC_ERR, 1));
	while (row[i] != 0 && first != NULL)
	{
		if (row[i] != '"' && row[i] != '\'')
			second = go_until_quote(data, row, &i);
		else if (row[i] == '"' || row[i] == '\'')
			second = quote_manager(data, row, &i, row[i]);
		if (second != NULL)
			first = fusion_first_second_block(data, first, second);
		else
			return (ft_free((void **)first), NULL);
	}
	return (first);
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
	char	*first;
	char	*second;
	int		i;

	i = 0;
	second = NULL;
	first = ft_strdup("");
	data->saved_errno = errno;
	if (!first)
		return (ft_error_parent_char(data, MALLOC_ERR, 1));
	while (content[i] != 0 && first != NULL)
	{
		if (content[i] != 0 && content[i] != '$')
			second = go_until_dollar(data, content, &i);
		else if (content[i] == '$')
			second = dollar_manager(data, content, &i, Q_NONE);
		if (second != NULL)
			first = fusion_first_second_block(data, first, second);
		else
			return (ft_free((void **)&first), NULL);
	}
	return (first);
}

int	content_splitted_manager(t_data *data, char **content_to_xpand)
{
	int		y;
	char	*temp;

	y = 0;
	temp = NULL;
	while (content_to_xpand[y] != NULL)
	{
		temp = ft_strdup(content_to_xpand[y]);
		data->saved_errno = errno;
		if (!temp)
			return (ft_error_parent_int(data, MALLOC_ERR, 1));
		ft_free((void **)&content_to_xpand[y]);
		content_to_xpand[y] = expand_in_quote(data, temp);
		ft_free((void **)&temp);
		if (!content_to_xpand[y])
			return (1);
		y++;
	}
	return (0);
}

char	*manage_before_split(t_data *data, char *content)
{
	char	*temp1;
	char	*temp2;

	temp2 = NULL;
	temp1 = expand_off_quote(data, content);
	if (!temp1)
		return (NULL);
	temp2 = ft_strtrim(temp1, " ");
	ft_free((void **)&temp1);
	if (!temp2)
		return (ft_error_parent_char(data, MALLOC_ERR, 1));
	return (temp2);
}

// NOTE: All contents of the nodes that are in the cmd linked list have to be
// manage with val_manager. For each content node, there is 3 steps :
//	1) we have to expand all content that is outside of quotes;
//	2) we have to split the content (spaces are the separators)
//	3) we have to expend inside quotes of all the lines of splitted_content;

int	val_manager(t_data *data)
{
	char	*temp;
	t_line	*current;

	current = data->line_cmd;
	while (current != NULL)
	{
		if (current->type == T_INPUT || current->type == T_OUTPUT_TRUNC
			|| current->type == T_OUTPUT_APPEND || current->type == T_COMMAND)
		{
			temp = manage_before_split(data, current->content);
			if (!temp)
				return (1);
			if (temp[0] == 0)
				return (ft_free((void **)&temp), 0);
			current->content_xpand = ft_split(temp, ' ');
			data->saved_errno = errno;
			ft_free((void **)&temp);
			if (!current->content_xpand)
				return (ft_error_parent_int(data, MALLOC_ERR, 1));
			if (content_splitted_manager(data, current->content_xpand) == 1)
				return (1);
		}
		current = current->next;
	}
	return (0);
}
