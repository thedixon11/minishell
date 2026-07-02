#include "../minishell_general.h"

// NOTE: With env_var_checker, we'll check if the env_var is in the
// environement or not.If not, we return NULL.
//
// NOTE: It is important to compare len of env_var + 1 to be sure there is a
// null terminated value that ends the value
//
// NOTE: the environement is stored in a linked list created at the beggining
// of the program.

char	*env_var_checker(t_env *env, char *var_env)
{
	t_env	*current;
	int		len;
	char	*xpansion_result;

	len = ft_strlen(var_env) + 1;
	current = env;
	while (current != NULL)
	{
		if (ft_strncmp(var_env, current->name, len) == 0)
		{
			xpansion_result = ft_strdup(current->content);
			if (!xpansion_result)
				return (ft_error_parent(B_TRUE, "malloc", 1));
			return (xpansion_result);
		}
		current = current->next;
	}
	xpansion_result = ft_strdup("");
	if (!xpansion_result)
		return (ft_error_parent(B_TRUE, "malloc", 1));
	return (xpansion_result);
}

// NOTE: Withe extract_env_var, we'll extract the env_var of the content.
// Then, we check with env_var checker if the value exists in the environment.
//
// NOTE: str may be either value, or inside_quote.
// i may be either i_value or i_quote.

char	*extract_env_var(char *str, int *i)
{
	int		end;
	int		len;
	char	*var_env;

	(*i)++;
	end = *i;
	len = 0;
	while (ft_isalnum(str[end]) == 1 || str[end] == '_')
		end++;
	len = end - *i;
	var_env = ft_substr(str, *i, len);
	if (!var_env)
		return (ft_error_parent(B_TRUE, "malloc", 1));
	*i = end;
	return (var_env);
}

// NOTE: When we know we deal with a possible env_var, here starts the
// process to manage it. There is 2 steps:
//	1) we extract the env_var of the content;
//	2) we check if the env_var exists in the environment
//
// NOTE: i may be either i_value, either i_quote depending situation.
// str may be either value or inside_quote depending situation.

char	*env_var_manager(t_data *data, char *str, int *i)
{
	char	*xpansion_result;
	char	*var_env;

	var_env = extract_env_var(str, i);
	if (!var_env)
		return (NULL);
	xpansion_result = env_var_checker(data->env, var_env);
	free(var_env);
	if (!xpansion_result)
		return (NULL);
	return (xpansion_result);
}
