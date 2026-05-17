
#include "minishell_expansion.h"

char  *seconc_block_not_dollar(char *inside_quote, int *i_quote)
{
    int end;
    int len;
    char  *second_block;

    end = *i_quote;
    len = 0;
    while (inside_quote[end] != '$' && inside_quote[end] != 0)
     end++;
    len = end - *i_quote;
    second_block = ft_substr(inside_quote, *i_quote, len);
    *i_quote = end;
    return (second_block);
}

char  *quote_expansion(t_data *data, char *inside_quote)
{
  char  *first_block;
  char  *second_block;
  char  *temp;
  int i_quote;

  // ici commence l'expansion
  // on travaille ici avec insique_quote, donc on prend comme index "i_quote", qui va commencer 
  // a zero. c'est i_quote qui va varier et pas i_str (index originel)
  // l'idee est de chaque fois fusionner le deuxieme block avec le premier block. le premier block
  // deviens la fusion de l'ancien premier et de l'ancien deuxieme .

  i_quote = 0;
  first_block = ft_strdup("");
  while (inside_quote[i_quote] != 0)
  {
    if (inside_quote[i_quote] != '$')
      second_block = seconc_block_not_dollar(inside_quote, &i_quote);
    else if (inside_quote[i_quote] == '$')
     second_block = dollar_manager(data, inside_quote, &i_quote, YES);
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

char  *extract_quote(char *content, int *i_content, char quote)
{
  char  *inside_quote;
  int end;
  int len;

  // on start depuis le quote d'entree. l'idee est de trouver 
  // l'emplacement du quote de fin. on doit incrementer start pour ne pas inclure 
  // le quote d'entree dans le inside_quote
  (*i_content)++;
  end = *i_content;
  while (str[end] != quote)
    end++;

  // on determine la len pour ensuite extraire le contenu avec substr et la retourner
  len = end - *i_content;
  inside_quote = ft_substr(str, *i_content, len);
  // je place l'index de la string apres la quote de fermeture
  *i_content = end + 1;

  return (inside_quote);
}

char  *quote_manager(t_data *data, char *content, int *i_content, char quote)
{
  char  *inside_quote;
  char  *quote_result;

  //on arrive dans cette fonction, lorsqu'on tombe sur une entree de quote.
  //la valeur de *i est l'emplacement de la quote d'entree dans str

  // la premiere etape est d'extraire le contenu qui se trouve
  // entre les quotes
  inside_quote = extract_quote(content, i_content, quote);

  // si l'on est dans des single quotes, alors il n'y a pas 
  // d'expansion, alors on peut retourner la string tel quelle
  if (quote == ''')
    quote_result = ft_strdup(inside_quote);

  //si l'on est dans des doubles quotes, alors on doit 
  //consider des possibles expansions
  else if (quote == '"')
    quote_result = quote_expansion(data, inside_quote);
  free(inside_quote);
  return (quote_result);
}
