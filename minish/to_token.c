#include "alex.h"

t_token	*to_token(char *line)
{
	t_state	state;
	state.i = 0;
	state.str = line;
	state.quote = '\0';
	state.head = NULL;
	state.current = NULL;
	while (state.str[state.i] != '\0')
	{
		if (state.str[state.i] == '\'' || state.str[state.i] == '"')
			handle_quote(&state);
		if (is_operator(state.str[state.i]) == 1)
			handle_operator(&state);
		if (state.str[state.i] == ' ')
			handle_space(&state);
		state.i++;
	}
	return (state.head);
}

void	handle_quote(t_state *state)
{
	int		start;
	char	*str;

	state->quote = state->str[state->i];
	start = state->i + 1;
	state->i = start;
	while (state->str[state->i] != state->quote && state->str[state->i] != '\0') 
			state->i++;
	if (state->quote != '\0' && state->str[state->i] == '\0')
	{
		printf("Erreur : Quote pas fermee bordel");
		return ;
	}
	str = ft_strndup(state->str + start, state-> i - start);
	state->i++;
	state->current = new_node(str, WORD);
	add_node(state->current, state);
}

void	handle_operator(t_state *state)
{
	int		start;
	char	*str;

	
}
