#include "minishell_xpansion.h"


char  *quote_expansion(t_data *data, char *inside_quote)
{
  char  *first_block;
  char  *second_block;
  char  *temp;
  int i_quote;

  //NOTE: ici commence l'expansion
  // on travaille ici avec insique_quote, donc on prend comme index "i_quote", qui va commencer 
  // a zero. c'est i_quote qui va varier et pas i_value (index originel)
  // l'idee est de chaque fois fusionner le deuxieme block avec le premier block. le premier block
  // deviens la fusion de l'ancien premier et de l'ancien deuxieme .

  i_quote = 0;
  first_block = ft_strdup("");
  while (inside_quote[i_quote] != 0)
  {
    if (inside_quote[i_quote] != '$')
      second_block = second_block_not_dollar(inside_quote, &i_quote, Q_DOUBLE);
    else if (inside_quote[i_quote] == '$')
     second_block = dollar_manager(data, inside_quote, &i_quote, Q_DOUBLE);
    if (second_block != NULL)
    {
      temp = first_block;
      first_block = ft_strjoin(temp, second_block);
      free(second_block);
      free (temp);
    }
  }
  return (first_block);
}

char  *extract_quote(char *value, int *i_value, char quote)
{
  char  *inside_quote;
  int end;
  int len;

  //NOTE: on start depuis le quote d'entree. l'idee est de trouver 
  // l'emplacement du quote de fin. on doit incrementer start pour ne pas inclure 
  // le quote d'entree dans le inside_quote
  (*i_value)++;
  end = *i_value;
  while (value[end] != quote)
    end++;

  //NOTE: on determine la len pour ensuite extraire le contenu avec substr et la retourner
  len = end - *i_value;
  inside_quote = ft_substr(content, *i_value, len);
  //NOTE: je place l'index de la string apres la quote de fermeture
  *i_value = end + 1;

  return (inside_quote);
}

char  *quote_manager(t_data *data, char *value, int *i_value, char quote)
{
  char  *inside_quote;
  char  *quote_result;

  //NOTE: on arrive dans cette fonction, lorsqu'on tombe sur une entree de quote.
  //la valeur de *i est l'emplacement de la quote d'entree dans str

  //NOTE: la premiere etape est d'extraire le contenu qui se trouve
  // entre les quotes
  inside_quote = extract_quote(value, i_value, quote);

  //NOTE: si l'on est dans des single quotes, alors il n'y a pas 
  //d'expansion, alors on peut retourner la string tel quelle
  if (quote == '\'')
    quote_result = ft_strdup(inside_quote);

  //NOTE: si l'on est dans des doubles quotes, alors on doit 
  //consider des possibles expansions
  else if (quote == '"')
    quote_result = quote_expansion(data, inside_quote);
  free(inside_quote);
  return (quote_result);
}
