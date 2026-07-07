#include "alex.h"

t_command *new_command(int index)
{
	t_command	*current;

	current = calloc(1, sizeof(t_command));
	if (!current)
		return (NULL);
	current->args = NULL;
	current->prev = NULL;
	current->next = NULL;
	current->index = index;
	return (current);
}

int	count_args(t_token *token)
{
	int	count;
	t_token *temp;

	count = 0;
	while (token != NULL && token->type != PIPE)
	{
		if (token->type == WORD)
			count += 1;
		temp = token->next;
		token = temp;
	}
	return (count);
}

t_redir	*new_redir(t_type type, char *file)
{
	
}