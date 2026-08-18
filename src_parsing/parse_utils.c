#include "../minishell_general.h"

t_line	*new_line(t_data *data, t_type type, int cmd_nb, char *content)
{
	t_line	*node;

	node = ft_calloc(1, sizeof(t_line));
	if (!node)
		return (error_token_int(data, I_CALLOC, LIBFT_ERR, 1), NULL);
	node->type = type;
	node->fd = -1;
	node->cmd_nb = cmd_nb;
	if (content)
	{
		node->content = ft_strdup(content);
		if (!node->content)
		{
			ft_free((void **)&node);
			return (error_token_int(data, I_STRDUP, LIBFT_ERR, 1), NULL);
		}
	}
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
