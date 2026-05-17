#include "minishell_xpansion.h"

char  *value_manager(t_data *data, char *value)
{
  // le traitement des valeurs commencent ici.  
  // l'idee est de chaque fois fusionner le deuxieme block avec le premier block. le premier block
  // deviens la fusion de l'ancien premier et de l'ancien deuxieme .


  int i_value;
  char  *first_block;
  char  *second_block;
  char  *temp;

  // on set l'index de value a zero et le premier first block est mis a "zero"
  i_value= 0;
  first_block = ft_strdup("");

  // un block peut avoir 3 types dans l'etage de value :
  // 1) normal (not dollar or quote)
  // 2) etre un dollar case
  // 3) etre un quote case
  // on repete la boucle jusqu'a ce que l'index arrrive a 0

  while (value[i_value] != 0)
  {
    if (value[i_value] != '$' && value[i_value] != '"' && value[i_value] != '\'')
      second_block = second_block_not_dollar_or_quote(value, &i_value, Q_NONE);
    else if (value[i_value] == '$')
      second_block = dollar_manager(data, value, &i_value, Q_NONE);
    else if (value[i_value] == '"' || value[i_value] == '\'')
      second_block = quote_manager(data, value, &i_value, value[i_value]);

    // si le block n'est pas NULL, alors on fusionne le second block avec le premier
    if (second_block != NULL)
    {
      temp = first_block;
      first_block = ft_strjoin(temp, second_block);
      free(second_block);
      free (temp);
    }
  }
}
