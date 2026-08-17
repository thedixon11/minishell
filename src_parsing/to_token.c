#include "../minishell_general.h"

t_token	*to_token(char *line, t_data *data)
{
	t_state	state;

	state.i = 0;
	state.start = 0;
	state.str = line;
	state.quote = '\0';
	state.head = NULL;
	state.current = NULL;
	while (state.str[state.i] != '\0')
	{
		if (state.str[state.i] == '\'' || state.str[state.i] == '"')
		{
			if (handle_quote(&state, data) == 1)
				return (NULL);
		}
		else if (is_operator(state.str[state.i]) == 1)
		{
			if (handle_operator(&state, data) == 1)
				return (NULL);
		}
		else if (state.str[state.i] == ' ')
		{
			handle_word(&state, data);
			state.start = state.i + 1;
		}
		state.i++;
	}
	handle_word(&state, data);
	return (state.head);
}

int	handle_quote(t_state *state, t_data *data)
{
	state->quote = state->str[state->i];
	state->i++;
	while (state->str[state->i] != state->quote && state->str[state->i] != '\0') 
			state->i++;
	if (state->quote != '\0' && state->str[state->i] == '\0')
		return (error_token(data, state, STAX_QUOTES, 2));
}

int	handle_operator(t_state *state, t_data *data)
{
	char	*str;
	t_type	type;

	handle_word(state);
	type = get_type(state);
	if (type == T_HEREDOC || type == T_OUTPUT_APPEND)
	{
		str = ft_substr(state->str, state->i, 2);
		state->i++;
	}
	else 
		str = ft_substr(state->str, state->i, 1);
	if (!str)
	{
		free_state_data(state);
		return (error_int(data, I_SUBSTR, LIBFT_ERR, 1));
	}
	state->current = new_node(str, type);
	add_node(state->current, state);
	state->start = state->i + 1;
	ft_free((void **)&str);
}

int	handle_word(t_state *state, t_data *data)
{
	char	*str;

	if (state->start != state->i)
	{
		str = ft_substr(state->str, state->start, state->i - state->start);
		if (!str)
		{
			free_state_data(state);	
			return (error_int(data, I_SUBSTR, LIBFT_ERR, 1));
		}
		state->current = new_node(str, T_COMMAND);
		ft_free((void **)&str);
		if (!state->current)
		{
			return (1);	
		}
		add_node(state->current, state);
		state->start = state->i;
	}
}
