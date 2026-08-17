#include "../minishell_general.h"

t_token	*new_node(t_data *data, t_state *state, char *value, t_type type)
{
	t_token *current;

	current = ft_calloc(1, sizeof(t_token));
	if (!current)
	{
		free_state_data(state);
		error_int(data, I_CALLOC, LIBFT_ERR, 1);
		return (NULL);
	}
	current->value = ft_strdup(value);
	if (!current->value)
	{
		ft_free((void **)&current->value)
		ft_free((void **)&current);
		free_state_data(state);
		error_int(data, I_CALLOC, LIBFT_ERR, 1);
		return (NULL);
	}
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
