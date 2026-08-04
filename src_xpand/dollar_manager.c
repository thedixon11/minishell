#include "../minishell_general.h"

char	*dollar_is_error_code(t_data *data, int *i)
{
	char	*result;

	result = ft_itoa(data->code);
	if (!result)
		return (error_char(data, I_ITOA, LIBFT_ERR, 1));
	*i += ft_strlen(result) + 1;
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

// NOTE: It's the entry point to deal with dollars. Managing the dollars depends
//	on which value is right after it. There is 5 possiblities :
//	1) a quote (single or double), and we are treating out of quotes (Q_NONE);
//		>> dollar and quote are deleted;
//	2) a digit;
//		>> dollar and digit are deleted;
//	3) an '?';
//		>> have to expand the last number error;
//	4) an alpha or an underscore;
//		>> possibly an env_val -> go to env_var_manager;
//	5) everything else (can also be a quote, if we're treating inside quote)
//
// NOTE: the value i can be either i_content or i_quote depending situation.
//	the value str can be either content or inside_quote depending situation.

// TODO: have to create the function to get the code number error

char	*dollar_manager(t_data *data, char *str, int *i, t_quote q_mode)
{
	char	*result;

	if (q_mode == Q_NONE && (str[*i + 1] == '"' || str[*i + 1] == '\''))
	{
		*i += 1;
		return (NULL);
	}
	else if (ft_isdigit(str[*i + 1] == 1))
	{
		*i += 2;
		return (NULL);
	}
	else if (str[*i + 1] == '?')
		return (dollar_is_error_code(data, i));
	else if (ft_isalpha(str[*i + 1]) == 1 || str[*i + 1] == '_')
	{
		result = env_var_manager(data, str, i);
		if (!result)
			return (NULL);
		return (result);
	}
	else
		return (dollar_not_alphanum_and_err(data, str, i));
}
