#include "minishell_xecution.h"

char	*rebuild_value(t_env *current)
{
	char	*temp;
	char	*rebuild_value;

	// NOTE: pour rebuild, une value :
	// on strjoin le nom de la value avec '=';
	// on strjoin value + '=' avec le contenu de la value
	temp = ft_strjoin(current->name, "=");
	rebuild_value = ft_strjoin(temp, current->content);
	free(temp);
	return (rebuild_value);
}

char	**env_converter_ll_to_array(t_env *env)
{
	t_env	*current;
	int		y;
	char	**converted_env;

	// NOTE: on a besoin de reconvertir l'environnement qui est en linked list en array
	// NOTE: permiere etape : compter combien de values se trouvent dans l'env
	y = 0;
	current = env;
	while (current != NULL)
	{
		current = current->next;
		y++;
	}
	// NOTE: on cree le double tableau.
	converted_env = ft_calloc(y + 1, sizeof(char *));
	if (!converted_env)
		return (NULL);
	// NOTE: on reset le curseur current au debut de l'env en ll.  il faut ensuite rebuild chaque
	// values dans le double tableau avec rebuild value
	current = env;
	y = 0;
	while (current != NULL)
	{
		converted_env[y] = rebuild_value(current);
		current = current->next;
		y++;
	}
	return (converted_env);
}
