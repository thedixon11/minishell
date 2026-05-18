#include "minishell_xpansion.h"

char  *dollar_manager(t_data *data, char *str, int *i, t_quote q_mode)
{
  //NOTE: i peut soit etre i_content soit i_quote, en depend de la situation
  // str peut soit etre content, soit inside_quote en depend de la situation

  char  *result;

  //NOTE: si ce qui suit le $ un quote (single ou double), alors
  //le $ est annule et efface SEULEMENT SI ON EST PAS EN QUOTE MODE
  if (q_mode == Q_NONE && (str[*i + 1] == '"' || str[*i + 1] == '\''))
  {
    *i += 1;
     return (NULL);
  }

  //NOTE: si ce qui suit le $ est un digit, alors le $ est annule et efface
  esle if (ft_isdigit(str[*i + 1] == 1)
  {
    *i += 2;
    return (NULL);
  }
  
  //NOTE: si ce qui suit le $ est un ?, alors on doit expandre le code d'erreur
  //de sortie la commande d'avant
  else if (str[*i + 1] == '?')
  {
    result = find_exit_error();//TODO: when possible, add $? functionality
    return (result);
  }

  //NOTE: si ce qui suit le $ est soit une lettre soit un underscore,
  // alors on doit checker si c'est une env var et si oui expandre
  else if (ft_isalpha(str[*i + 1]) == 1 || str[*i + 1] == '_')
  {
    result = env_var_manager(data, str, i);
    return (result);
  }

  //NOTE: si ce qui suit le $ est autre chose,
  // on considere le $ et le char qui le suit comme normaux (pas un cas special)
  else
  {
    result = ft_calloc(3, sizeof(char));
    result[0] = '$';
    result[1] = str[*i + 1];
    *i += 2;
    return (result);
  }
}
