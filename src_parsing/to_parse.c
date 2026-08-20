#include "../minishell_general.h"

int	handle_token_line(t_data *data)
{
	int		error;
	int		cmd_nb;
	t_token	*current;

	error = 0;
	cmd_nb = 0;
	current = data->token_head;
	while (current != NULL)
	{
		if (current->type == T_COMMAND)
			error = handle_command(data, current, cmd_nb);
		else if (current->type == T_PIPE)
			error = handle_pipe(data, &cmd_nb);
		else
		{
			if (handle_redir(data, current, cmd_nb) == 1)
				return (1);
			current = current->next;
		}
		if (error != 0)
			return (1);
		current = current->next;
	}
	data->max_cmd_nb = cmd_nb;
	return (0);
}

int	to_parse(t_data *data)
{
	if (handle_token_line(data) == 1)
		return (1);
	if (fusion_commands(data) == 1)
		return (1);
	return (0);
}

int	handle_command(t_data *data, t_token *current, int cmd_nb)
{
	t_line	*new_cmd_node;
	char	*value;

	value = ft_strdup(current->value);
	if (!value)
		return (error_token_int(data, I_STRDUP, LIBFT_ERR, 1));
	new_cmd_node = new_line(data, current->type, cmd_nb, value);
	ft_free((void **)&value);
	if (!new_cmd_node)
		return (1);
	add_line(data, new_cmd_node);
	return (0);
}

int	handle_pipe(t_data *data, int *cmd_nb)
{
	t_line	*new_pipe_out_node;
	t_line	*new_pipe_in_node;

	new_pipe_out_node = new_line(data, T_PIPE_OUT, *cmd_nb, NULL);
	if (!new_pipe_out_node)
		return (1);
	add_line(data, new_pipe_out_node);
	(*cmd_nb)++;
	new_pipe_in_node = new_line(data, T_PIPE_IN, *cmd_nb, NULL);
	if (!new_pipe_in_node)
		return (1);
	add_line(data, new_pipe_in_node);
	return (0);
}

int	handle_redir(t_data *data, t_token *token, int cmd_nb)
{
	t_line	*new_redir_node;
	char	*value;

	if (token->next == NULL)
	{
		data->do_i_exit = B_FALSE;
		error_token_int(data, NULL, STAX_NEWL, 2);
		data->do_i_exit = B_TRUE;
		return (1);
	}
	value = ft_strdup(token->next->value);
	if (!value)
		return (error_token_int(data, I_STRDUP, LIBFT_ERR, 1));
	new_redir_node = new_line(data, token->type, cmd_nb, value);
	ft_free((void **)&value);
	if (!new_redir_node)
		return (1);
	add_line(data, new_redir_node);
	return (0);
}
