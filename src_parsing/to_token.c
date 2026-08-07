#include "../minishell_general.h"

t_token	*to_token(char *line)
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
			handle_quote(&state);
		else if (is_operator(state.str[state.i]) == 1)
			handle_operator(&state);
		else if (state.str[state.i] == ' ')
		{
			handle_word(&state);
			state.start = state.i + 1;
		}
		state.i++;
	}
	handle_word(&state);
	return (state.head);
}

void	handle_quote(t_state *state)
{
	state->quote = state->str[state->i];
	state->i++;
	while (state->str[state->i] != state->quote && state->str[state->i] != '\0') 
			state->i++;
	if (state->quote != '\0' && state->str[state->i] == '\0')
	{
		printf("Erreur : Quote pas fermee bordel\n");
		return ;
	}
}

void	handle_operator(t_state *state)
{
	char	*str;
	t_type	type;

	handle_word(state);
	type = get_type(state);
	if (type == T_HEREDOC || type == T_OUTPUT_APPEND)
	{
		str = strndup(state->str + state->i, 2);
		state->i++;
	}
	else 
		str = strndup(state->str + state->i, 1);
	state->current = new_node(str, type);
	add_node(state->current, state);
	state->start = state->i + 1;
	ft_free((void **)&str);
}

void	handle_word(t_state *state)
{
	char	*str;

	if (state->start != state->i)
	{
		str = strndup(state->str + state->start, state->i - state->start);
		state->current = new_node(str, T_COMMAND);
		add_node(state->current, state);
		state->start = state->i;
		ft_free((void **)&str);
	}
}
