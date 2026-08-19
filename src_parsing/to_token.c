#include "../minishell_general.h"

void	state_init(t_state *state, char *line)
{	
	state->i = 0;
	state->start = 0;
	state->str = line;
	state->quote = '\0';
}

int	to_token(char *line, t_data *data)
{
	t_state	state;
	int	error;

	error = 0;
	state_init(&state, line);
	while (state.str[state.i] != '\0')
	{
		if (state.str[state.i] == '\'' || state.str[state.i] == '"')
			error = handle_quote(&state, data);
		else if (is_operator(state.str[state.i]) == 1)
			error = handle_operator(&state, data);
		else if (state.str[state.i] == ' ')
		{
			error = handle_word(&state, data);
			state.start = state.i + 1;
		}
		if (error != 0)
			return (1);
		state.i++;
	}
	error = handle_word(&state, data);
	if (error != 0)
		return (1);
	return (0);
}

int	handle_quote(t_state *state, t_data *data)
{
	data->do_i_exit = B_FALSE;
	state->quote = state->str[state->i];
	state->i++;
	while (state->str[state->i] != state->quote && state->str[state->i] != '\0') 
			state->i++;
	if (state->quote != '\0' && state->str[state->i] == '\0')
	{
		error_token_int(data, NULL, STAX_QUOTES, 2);
		data->do_i_exit = B_TRUE;
		return (1);
	}
	return (0);
}

int	handle_operator(t_state *state, t_data *data)
{
	char	*operator;
	t_type	type;
	t_token	*new_node;

	if (handle_word(state, data) != 0)
		return (1);
	type = get_type(state);
	if (type == T_HEREDOC || type == T_OUTPUT_APPEND)
	{
		operator = ft_substr(state->str, state->i, 2);
		state->i++;
	}
	else 
		operator = ft_substr(state->str, state->i, 1);
	if (!operator)
		return (error_token_int(data, I_SUBSTR, LIBFT_ERR, 1));
	new_node = new_token_node(data, operator, type);
	ft_free((void **)&operator);
	if (!new_node)
		return (1);
	add_token(data, new_node);
	state->start = state->i + 1;
	return (0);
}

int	handle_word(t_state *state, t_data *data)
{
	char	*word;
	t_token	*new_node;

	if (state->start != state->i)
	{
		word = ft_substr(state->str, state->start, state->i - state->start);
		if (!word)
			return (error_token_int(data, I_SUBSTR, LIBFT_ERR, 1));
		new_node = new_token_node(data, word, T_COMMAND);
		ft_free((void **)&word);
		if (!new_node)
			return (1);
		add_token(data, new_node);
		state->start = state->i;
	}
	return (0);
}
