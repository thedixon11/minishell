#include "minishell_xecution.h"

char  *rebuild_value(t_env *current)
{
  char  *temp;
  char  *rebuild_value;

  temp = ft_strjoin(current->name, "=");
  rebuild_value = ft_strjoin(temp, current->content);
  free (temp);
  return (rebuild_value);
}


char  **env_converter_ll_to_array(t_env *env)
{
  //NOTE: on a besoin de reconvertir l'environnement qui est en linked list en array

  t_env *current;
  int y;
  char  **converted_env;

  y = 0;
  current = env;
  while (current != NULL)
  {
    current = current->next;
    y++;
  }
  converted_env = ft_calloc(y + 1, sizeof(char *));
  if (!converted_env)
    return (NULL);
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
