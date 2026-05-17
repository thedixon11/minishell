#include "minishell_xpansion.h"

char  *env_var_checker(t_env *env, char *var_env)
{
  t_env *current;
  int len;
  char  *xpansion_result;

  //ici, on va comparer notre var_env et voir si elle existe dans l'environnement
  //il est important de comparer la len de var_env + 1 (inclus le /0) pour etre sur
  //qu'il n'y ait rien apres.
  //a noter que l'environnement est stocker dans une double liste chainee, contentant
  //pour chaque node : name, content, prev et next
  len = ft_strlen(var_env) + 1;
  current = env;
  while (current != NULL)
  {
    if (ft_strncpy(var_env, current->name, len) == 0)
    {
      xpansion_result = ft_strdup(current->content);
      return (xpansion_result);
    }
    current = current->next;
  }
  return (NULL);
}

char  *extract_env_var(char *str, int *i)
{
  int end;
  int len;
  char  *var_env;

  // str peut etre soit value soit inside_quote
  // i peut etre soit i_value soit i_quote

  //pour extraire la env_var, on doit determiner la fin de celle-ci
  //toute env_var ne peut conternir que des lettres, digits et underscore
  //elle ne peut pas commencer par un digit

  (*i)++;
  end = *i;
  len = 0;
  while(ft_isalnum(str[end]) == 1 || str[end] == '_')
    end++;
  
  //une fois la fin de la var_env trouvee, on va l'extraire de la str
  //grace a substr. on a besoin pour ca de la len de la var_env
  len = end - *i;
  var_env = ft_substr(str, *i, len);

  // on place i juste apres la env var
  *i = end;
  return (var_env);
}

char  *env_var_manager(t_data *data, char *str, int *i)
{
  // i peut soit etre i_value, soit i_quote en depend de la situation
  // str peut soit etre value, soit inside_quote en depend de la situation

  char  *xpansion_result;
  char  *var_env;

  //pour commencer, il faut qu'on extraie la var env potentielle
  //contenue dans la string
  var_env = extract_env_var(str, i);

  //une fois la env_var extraite, on va checker si elle existe bien
  //dans notre environnement, et si oui, on va l'expand
  xpansion_result = env_var_checker(data->env, var_env);
  free(var_env);
  return (xpansion_result);
}
