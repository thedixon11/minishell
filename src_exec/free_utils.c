#include "../minishell_general.h"

void	free_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current->next != NULL)
	{
		if (current->name != NULL)
			ft_free((void **)&current->name);
		if (current->content != NULL)
			ft_free((void **)&current->content);
		current = current->next;
		if (current->prev != NULL)
			ft_free((void **)&current->prev);
	}
	if (current->name != NULL)
		ft_free((void **)&current->name);
	if (current->content != NULL)
		ft_free((void **)&current->content);
	ft_free((void **)&current);
}

void	free_line_cmd(t_line *line_cmd)
{
	t_line	*current;

	current = line_cmd;
	while (current->next != NULL)
	{
		if (current->content != NULL)
			ft_free((void **)&current->content);
		if (current->content_xpand != NULL)
			ft_free_tab(&current->content_xpand);
		current = current->next;
		ft_free((void **)&current->prev);
	}
	if (current->content != NULL)
		ft_free((void **)&current->content);
	if (current->content_xpand != NULL)
		ft_free_tab(&current->content_xpand);
	ft_free((void **)&current);
}
