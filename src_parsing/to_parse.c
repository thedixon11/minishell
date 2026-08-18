#include "../minishell_general.h"
#include "minishell_parsing.h"

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
					ft_free((void **)&current->content);
					current->content = ft_strjoin(resultat, skip->content);
					ft_free((void **)&resultat);
					temp = skip;
					skip->prev->next = temp->next;
					if (temp->next != NULL)
						temp->next->prev = temp->prev;
					skip = temp->next;
					ft_free((void **)&temp->content);
					ft_free((void **)&temp);
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
	t_line	*result;
	t_token	*token;
	int	error;

	cmd_nb = 0;
	line_head = NULL;
	token = head;
	error = 0;
	data->line_cmd = head;
	while (token != NULL)
	{
		if (token->type == T_COMMAND)
			error = handle_command(data, token, &line_head, cmd_nb);
		else if (token->type == T_PIPE)
			error = handle_pipe(data, &cmd_nb, &line_head);
		else
		{
			if (handle_redir(data, token, cmd_nb, &line_head) == 1)
				break ;  // WARNING: wtf ? sort de la boucle et apres il fait quand meme fusion_commands ?
			token = token->next;
		}
		token = token->next;
	}
	result = fusion_commands(data, line_head);
	data->max_cmd_nb = cmd_nb;
	return (result);
}

int	handle_command(t_data *data, t_token *token, t_line **head, int cmd_nb)
{
	t_line	*current;
	char	*value;
	
	value = ft_strdup(token->value);
	if (!value)
		return (error_token_int(data, I_STRDUP, LIBFT_ERR, 1));
	current = new_line(data, token->type, cmd_nb, value);
	ft_free((void **)&value);
	if (!current)
		return (1);
	add_line(current, head);
	return (0);
}

int	handle_pipe(t_data *data, int *cmd_nb, t_line **head)
{
	t_line	*current;

	current = new_line(T_PIPE_OUT, *cmd_nb, NULL);
	if (!current)
		return (1);
	add_line(current, head);
	(*cmd_nb)++;
	current = new_line(T_PIPE_IN, *cmd_nb, NULL);
	if (!current)
		return (1);
	add_line(current, head);
	return (0);
}

int	handle_redir(t_data *data, t_token *token, int cmd_nb, t_line **head)
{
	t_line	*current;
	char	*value;

	if (token->next == NULL)
	{
		data->do_i_exit = B_FALSE;
		error_token_int(data, NULL, STAX_REDIR, 2);
		data->do_i_exit = B_TRUE;
		return (1);
	}
	value = ft_strdup(token->next->value);
	if (!value)
		return (error_token_int(data, I_STRDUP, LIBFT_ERR, 1));
	current = new_line(token->type, cmd_nb, value);
	ft_free((void **)&value);
	if (!current)
		return (1);
	add_line(current, head);
	return (0);
}
