
#include "minishell_expansion.h"

char  *seconc_block_not_dollar(char *str, int *start)
{
    int end;
    char  *second_block;

    end = *start;
    while (inside_quote[end + 1] != '$')
     end++;
    second_block = ft_substr(inside_quote, start, end - start);
    *start = end;
    return (second_block);
}

char  *quote_expansion(t_data *data, char *inside_quote)
{
  char  *first_block;
  char  *second_block;
  char  *temp;
  int start;

  start = 0;
  first_block = ft_strdup("");
  while (inside_quote[start] != 0)
  {
    if (inside_quote[end] != "$")
      second_block = seconc_block_not_dollar(inside_quote, &start);
    else if (inside_quote[end] == "$")
     second_block = dollar_manager(data, inside_quote, &start, YES);
    temp = first_block;
    first_block = ft_strjoin(temp, second_block);
    free (temp);
  }
}

char  *extract_quote(char *str, int start, char quote)
{
  char  *inside_quote;
  int end;
  int len;

  // on start depuis le quote d'entree. l'idee est de trouver 
  // l'emplacement du quote de fin. 
  start++;
  end = start;
  end = 0;
  while (str[end] != quote)
    end++;

  // on determine la len pour ensuite extraire le contenu avec substr et la retourner
  len = end - start;
  inside_quote = ft_substr(str, start, len);
  return (inside_quote);
}

char  *quote_manager(t_data *data, char *str, int *i, char quote)
{
  char  *inside_quote;
  char  *quote_result;

  //on arrive dans cette fonction, lorsqu'on tombe sur une entree de quote.
  //la valeur de *i est l'emplacement de l'entree de la quote dans str

  // la premiere etape est d'extraire le contenu qui se trouve
  // entre les quotes
  inside_quote = extract_quote(str, i, quote);

  // si l'on est dans des single quotes, alors il n'y a pas 
  // d'expansion, alors on peut retourner la string tel quelle
  if (quote == ''')
  {
    quote_result = inside_quote;
    return (quote_result);
  }
  
  //si l'on est dans des doubles quotes, alors on doit 
  //consider des possibles expansions
  else if (quote == '"')
    quote_result = quote_expansion(inside_quote);
  return (quote_result);
}
