#include "../minishell_general.h"

t_token	*new_node(char *value, t_type type)
{
	t_token *current;

	current = ft_calloc(1, sizeof(t_token)); 
	if (!current)
		return (NULL);
	current->value = value;
	current->type = type;
	current->next = NULL;
	current->prev = NULL;
	return (current);
}

void	add_node(t_token *current, t_state *state)
{
	t_token	*temp;

	if (state->head == NULL)
		state->head = current;
	else
	{
		temp = state->head;
		while (temp->next != NULL)
			temp = temp->next;
		current->next = NULL;
		current->prev = temp;
		temp->next = current;
	}
}
