#include "../minishell_general.h"

char	*esle_after_dollar_hdoc(t_data *data, char *str, int *i)
{
	char	*result;

	result = ft_calloc(3, sizeof(char));
	if (!result)
		return (error_char(data, I_CALLOC, LIBFT_ERR, 1));
	result[0] = '$';
	result[1] = str[*i + 1];
	*i += 2;
	return (result);
}

char	*quote_after_dollar_hdoc(t_data *data, int *i)
{
	char	*result;

	*i += 1;
	result = ft_strdup("");
	if (!result)
		return (error_char(data, I_STRDUP, LIBFT_ERR, 1));
	return (result);
}

char	*zero_after_dollar_hdoc(t_data *data, int *i)
{
	char	*result;

	*i += 1;
	result = ft_calloc(2, sizeof(char));
	if (!result)
		return (error_char(data, I_CALLOC, LIBFT_ERR, 1));
	result[0] = '$';
	return (result);
}

char	*dollar_manager_hdoc(t_data *data, char *str, int *i)
{
	if ((str[*i + 1] == '"') || (str[*i + 1] == '\''))
		return (quote_after_dollar(data, i));
	else if (str[*i + 1] == 0)
		return (zero_after_dollar(data, i));
	else
		return (esle_after_dollar_hdoc(data, str, i));
}

char	*expand_off_quote_hdoc(t_data *data, char *content)
{
	char	*first;
	char	*second;
	int		i;

	i = 0;
	second = NULL;
	first = ft_strdup("");
	if (!first)
		return (error_char(data, I_STRDUP, LIBFT_ERR, 1));
	while (content[i] != 0 && first != NULL)
	{
		if (content[i] != 0 && content[i] != '$')
			second = go_until_dollar(data, content, &i);
		else if (content[i] == '$')
			second = dollar_manager_hdoc(data, content, &i);
		if (second != NULL)
			first = fusion_first_second_block(data, first, second);
		else
			return (ft_free((void **)&first), NULL);
	}
	return (first);
}
