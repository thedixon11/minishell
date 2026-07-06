#include "../minishell_general.h"
#include "minishell_xecution.h"
#include <unistd.h>

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
	data->saved_errno = errno;
	if (!inside_quote)
		return (ft_error_parent_char(data, MALLOC_ERR, 1));
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
	data->saved_errno = errno;
	if (!second_block)
		return (ft_error_parent_char(data, MALLOC_ERR, 1));
	*start = end;
	return (second_block);
}

// NOTE: delimiter manager will treat the quotes of the delimiter and removed them

char	*delimiter_manager_hdoc(t_data *data, char *old_del)
{
	char	*first_block;
	char	*second_block;
	char	*temp;
	int		i;

	i = 0;
	first_block = ft_strdup("");
	data->saved_errno = errno;
	if (!first_block)
		return (ft_error_parent_char(data, MALLOC_ERR, 1));
	while (old_del[i] != 0)
	{
		if (old_del[i] != '\'' && old_del[i] != '\"' && old_del[i] != 0)
			second_block = go_until_quote_hdoc(data, old_del, &i);
		else if (old_del[i] == '\'' || old_del[i] != '\"')
			second_block = extract_quote_hdoc(data, old_del, &i, old_del[i]);
		if (second_block != NULL)
		{
			temp = first_block;
			first_block = ft_strjoin(temp, second_block);
			data->saved_errno = errno;
			ft_free((void**)&temp);
			ft_free((void**)&second_block);
			if (!first_block)
				return (ft_error_parent_char(data, MALLOC_ERR, 1));	
		}
		else 
		{
			ft_free((void**)&first_block);
			return (NULL);
		}
	}
	return (first_block);
}
