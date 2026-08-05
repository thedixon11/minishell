#include "../minishell_general.h"

t_env	*create_env(char **envp)
{
	int		x;
	t_env	*head;
	t_env	*node;

	x = 0;
	head = NULL;
	while (envp[x] != NULL)
	{
		node = new_node_env(envp[x]);
		add_node_env(node, &head);
		x++;
	}
	return (head);
}

void	add_node_env(t_env	*current, t_env **head)
{
	t_env	*temp;

	if (*head == NULL)
		*head = current;
	else
	{
		temp = *head;
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

	node = ft_calloc(1, sizeof(t_env));
	if (!node)
		return (NULL);
	equal = ft_strchr(line, '=');
	node->name = ft_strndup(line, equal - line);
	node->content = ft_strdup(equal + 1);
	return (node);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*str;

	str = ft_calloc(1, n + 1);
	if (!str)
		return (NULL);
	ft_strlcpy(str, s, n + 1);
	return (str);
}
