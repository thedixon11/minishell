#include "alex.h"

t_line *fusion_commands(t_line *head)
{
	t_line	*current;
	char	*resultat;
	t_line	*temp;

	current = head;
	while (current != NULL)
	{
		while (current->next != NULL && current->next->type == T_COMMAND && current->cmd_nb == current->next->cmd_nb)
		{
			if (current->type == T_COMMAND)
			{
				resultat = ft_strjoin(current->content, " ");
				current->content = ft_strjoin(resultat, current->next->content);
				temp = current->next;
				current->next = temp->next;
				if (temp->next != NULL)
					temp->next->prev = current;
				free(temp);	
			}
		}
		current = current->next;
	}
	return (head);
}

t_line	*to_parse(t_token *head)
{
	int	cmd_nb;
	t_line	*line_head;
	t_token	*token;

	cmd_nb = 0;
	line_head = NULL;
	token = head;
	while (token != NULL)
	{
		if (token->type == T_COMMAND)
			handle_command(token, &line_head, cmd_nb);
		else if (token->type == T_PIPE)
			handle_pipe(&cmd_nb, &line_head);
		else
		{
			if (handle_redir(token, cmd_nb, &line_head) == -1)
				break ;
			token = token->next;
		}
		token = token->next;
	}
	line_head = fusion_commands(line_head);
	return (line_head);
}

void	handle_command(t_token *token, t_line **head, int cmd_nb)
{
	t_line	*current;

	current = new_line(token->type, cmd_nb, token->value);
	add_line(current, head);
}

void	handle_pipe(int *cmd_nb, t_line **head)
{
	t_line	*current;

	current = new_line(T_PIPE_OUT, *cmd_nb, NULL);
	add_line(current, head);
	(*cmd_nb)++;
	current = new_line(T_PIPE_IN, *cmd_nb, NULL);
	add_line(current, head);
}

int	handle_redir(t_token *token, int cmd_nb, t_line **head)
{
	t_line	*current;

	if (token->next == NULL)
	{
		printf("Erreur : Syntax error\n");
		return (-1);
	}
	current = new_line(token->type, cmd_nb, token->next->value);
	add_line(current, head);
	return (0);
}
