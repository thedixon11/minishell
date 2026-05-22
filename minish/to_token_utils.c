#include "alex.h"

int	is_operator(char c)
{
	if ( c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

t_type	get_type(t_state *state)
{
	if (state->str[state->i] == '|')
		return (PIPE);
	if (state->str[state->i] == '>' && state->str[state->i + 1] == '>')
		return (REDIR_APPEND);
	if (state->str[state->i] == '<' && state->str[state->i + 1] == '<')
		return (HEREDOC);
	if (state->str[state->i] == '<')
		return (REDIR_IN);
	if (state->str[state->i] == '>')
		return (REDIR_OUT);
	return (WORD);
}
