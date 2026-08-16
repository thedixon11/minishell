#include "../minishell_general.h"

char	*dollar_is_error_code(t_data *data, int *i)
{
	char	*result;

	result = ft_itoa(data->code);
	*i += 2;
	if (!result)
		return (error_char(data, I_ITOA, LIBFT_ERR, 1));
	return (result);
}

char	*dollar_not_alphanum_and_err(t_data *data, char *str, int *i)
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

char	*digit_after_dollar(t_data *data, int *i)
{
	char	*result;

	*i += 2;
	result = ft_strdup("");
	if (!result)
		return (error_char(data, I_STRDUP, LIBFT_ERR, 1));
	return (result);
}

char	*quote_after_dollar(t_data *data, int *i)
{
	char	*result;

	*i += 1;
	result = ft_strdup("");
	if (!result)
		return (error_char(data, I_STRDUP, LIBFT_ERR, 1));
	return (result);
}

char	*zero_after_dollar(t_data *data, int *i)
{
	char	*result;

	*i += 1;
	result = ft_calloc(2, sizeof(char));
	if (!result)
		return (error_char(data, I_CALLOC, LIBFT_ERR, 1));
	result[0] = '$';
	return (result);
}
