#include "../minishell_general.h"

t_line *fusion_commands(t_line *head)
{
	t_line	*current;
	char	*resultat;
	t_line	*temp;
	t_line	*skip;

	current = head;
	while (current != NULL)
	{
		if (current->type == T_COMMAND)
		{
			skip = current->next;
			while (skip != NULL && skip->cmd_nb == current->cmd_nb && skip->type != T_PIPE_OUT)
			{
				if (skip->type == T_COMMAND)
				{
					resultat = ft_strjoin(current->content, " ");
					current->content = ft_strjoin(resultat, skip->content);
					temp = skip;
					skip->prev->next = temp->next;
					if (temp->next != NULL)
						temp->next->prev = temp->prev;
					skip = temp->next;
					free(temp);
				}
				else
				skip = skip->next;
			}
		}
			current = current->next;
	}
	return (head);
}

t_line	*to_parse(t_data *data, t_token *head)
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
	data->max_cmd_nb = cmd_nb;
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
