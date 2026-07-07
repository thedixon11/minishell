#include "alex.h"

t_command *to_parse(t_token *head)
{
	t_token		*current_token;
	t_command	*current;
	int			count;
	int			i;

	i = 0;
	current_token = head;
	current = new_command(0);
	count = count_args(head);
	current->args = malloc((count + 1) * sizeof(char *));
	while (current_token != NULL)
	{
		if (current_token->type == WORD)
		{
			current->args[i] = current_token->value;
			i++;
		}
		else if (current_token->type == PIPE)
		{}
		else
		{
			current->redir = new_redir(current_token->type, current_token->next->value);
			add_redir()
		}
	current_token = current_token->next;
	}
	current->args[i] = NULL;
	return(current);
}
