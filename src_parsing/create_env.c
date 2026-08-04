#include "../minishell_general.h"

t_env	*create_env(char **envp)
{
	int		x;
	t_env	*head;
	t_env	*node;

	x = 0;
	while (envp[x] != NULL)
	{

	}
}

void	add_node_env(t_env *head)
{
	t_env	*temp;
	t_env	*current;

	if (head == NULL)
		head = current;
	else
	{
		temp = head;
		while (temp->next != NULL)
			temp = temp->next;
		current->next = NULL;
		current->prev = temp;
		temp->next = current;
	}
}

t_env	*new_node_env(char *line)
{
	t_env	*node;
	char	*equal;

	node = calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	equal = ft_strchr(line, '=');
	node->name = ft_strndup(line, equal - line);
	node->content = strdup(equal + 1);
	return (node);
}
