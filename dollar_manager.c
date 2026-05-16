char  *dollar_manager(t_data *data, char *str, int *i)
{
  char  *result;
  //si ce qui suit le $ est un digit ou un quote (single ou double), alors
  //le $ est annule et efface
  if (ft_isdigit(str[*i + 1] == 1 || str[*i + 1] == '"' || str[*i + 1] == ''')
  {
    *i += 1;
    return (NULL);
  }

//si ce qui suit le $ est un ?, alors on doit expandre le code d'erreur
//de sortie la commande d'avant
  else if (str[*i + 1] == '?')
  {
    result = find_exit_error();
    return (result);
  }

//si ce qui suit le $ est soit une lettre soit un underscore,
// alors on doit checker si c'est une env var et si oui expandre
  else if (ft_isalpha(str[*i + 1]) == 1 || str[*i + 1] == '_')
  {
    result = env_var_manager(data, str, i);
    return (result);
  }

// si ce qui suit le $ est autre chose,
// on considere le $ et le char qui le suit comme normaux (pas un cas special)
  else
  {
    result = ft_calloc(3, sizeof(char));
    result[0] = '$';
    result[1] = str[*i + 1];
    return (result);
  }
}
