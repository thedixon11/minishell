#include "../minishell_general.h"

t_line	*new_line(t_data *data, t_type type, int cmd_nb, char *content)
{
	t_line	*new_node_line;

	new_node_line = ft_calloc(1, sizeof(t_line));
	if (!new_node_line)
		return (error_token_int(data, I_CALLOC, LIBFT_ERR, 1), NULL);
	new_node_line->type = type;
	new_node_line->fd = -1;
	new_node_line->cmd_nb = cmd_nb;
	if (content != NULL)
	{
		new_node_line->content = ft_strdup(content);
		if (!new_node_line->content)
		{
			ft_free((void **)&new_node_line);
			return (error_token_int(data, I_STRDUP, LIBFT_ERR, 1), NULL);
		}
	}
	return (new_node_line);
}

void	add_line(t_data *data, t_line *current)
{
	t_line	*temp;

	if (data->line_cmd == NULL)
		data->line_cmd = current;
	else
	{
		temp = data->line_cmd;
		while (temp->next != NULL)
			temp = temp->next;
		current->next = NULL;
		current->prev = temp;
		temp->next = current;
	}
}
