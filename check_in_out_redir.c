#include "minishell_xecution.h"

// TODO: have to add the fact he will just check the nodes of the right number cmd

t_bool check_in_out_redir(t_line *line_cmd, int current_cmd_nb)
{
	t_line	*current;
	int	y;

	y = 0;
	current = line_cmd;
  while (current->cmd_nb != current_cmd_nb)
    current = current->next;
	while (current->cmd_nb == current_cmd_nb && current != NULL)
	{
		y = 0;
		if (current->type == T_INPUT || current->type == T_OUTPUT_APPEND
			|| current->type == T_OUTPUT_TRUNC)
		{
			while (current->content_xpand[y] != NULL)
				y++;
		}
		if (y > 1)
			return (B_FALSE);
		current = current->next;
	}
	return (B_TRUE);
}
