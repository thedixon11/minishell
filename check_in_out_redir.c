#include "minishell_xecution.h"

// TODO: have to add the fact he will just check the nodes of the right number cmd

int	check_in_out_redir(t_line *cmd_line)
{
	t_line	*current;
	int	y;

	y = 0;
	current = cmd_line;
	while (current != NULL)
	{
		y = 0;
		if (current->type == T_INPUT || current->type == T_OUTPUT_APPEND
			|| current->type == T_OUTPUT_TRUNC)
		{
			while (current->content_xpand[y] != NULL)
				y++;
		}
		if (y > 1)
			return (1);
		current = current->next;
	}
	return (0);
}
