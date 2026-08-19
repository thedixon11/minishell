#include "../minishell_general.h"

int	join_all_cmd_content(t_data *data, t_line *current, t_line *to_fusion)
{
	char	*resultat;
	t_line	*temp;

	resultat = ft_strjoin(current->content, " ");
	ft_free((void **)&current->content);
	if (!resultat)
		return (error_token_int(data, I_STRJOIN, LIBFT_ERR, 1));
	current->content = ft_strjoin(resultat, to_fusion->content);
	ft_free((void **)&resultat);
	if (!current->content)
		return (error_token_int(data, I_STRJOIN, LIBFT_ERR, 1));
	temp = to_fusion;
	to_fusion->prev->next = temp->next;
	if (temp->next != NULL)
		temp->next->prev = temp->prev;
	ft_free((void **)&temp->content);
	ft_free((void **)&temp);
	return (0);
}

int	move_skip(t_data *data, t_line *current)
{
	t_line	*skip;
	t_line	*to_fusion;

	skip = current->next;
	while (skip != NULL && skip->cmd_nb == current->cmd_nb
		&& skip->type != T_PIPE_OUT)
	{
		if (skip->type == T_COMMAND)
		{
			to_fusion = skip;
			skip = skip->next;
			if (join_all_cmd_content(data, current, to_fusion) == 1)
				return (1);
		}
		else
			skip = skip->next;
	}
	return (0);
}

int	fusion_commands(t_data *data)
{
	t_line	*current;

	current = data->line_cmd;
	while (current != NULL)
	{
		if (current->type == T_COMMAND)
		{
			if (move_skip(data, current) == 1)
				return (1);
		}
		current = current->next;
	}
	return (0);
}
