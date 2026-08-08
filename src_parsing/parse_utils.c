#include "../minishell_general.h"

t_line	*new_line(t_type type, int cmd_nb, char *content)
{
	t_line	*node;

	node = calloc(1, sizeof(t_line)); // BUG:
	if (!node)
		return (NULL);
	node->type = type;
	node->fd = -1;
	node->cmd_nb = cmd_nb;
	if (content)
		node->content = ft_strdup(content);
	// else
	// 	node->content = ft_strdup("");
	return (node);
}

void	add_line(t_line *current, t_line **head)
{
	t_line	*temp;

	if (*head == NULL)
		*head = current;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		current->next = NULL;
		current->prev = temp;
		temp->next = current;
	}
}
