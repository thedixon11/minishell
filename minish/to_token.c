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
		{
			handle_quote(&state);
		}
		if (is_operator(state.str[state.i] == 1))
		{
		}
	}
}

void	handle_quote(t_state *state)
{
	int	start;

	state->quote = state->str[state->i];
	start = state->i + 1;
	state->i = start;
	while (state->str[state->i] != state->quote)
	{
		if (state->str[state->i] == state->quote)
		{

		}
		else 
			state->i++;
	}
}