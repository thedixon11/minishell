#include "minishell_xpansion.h"

//NOTE: nouvelle fonction d'entree pour l'expansion (upgrade)

char  *go_until_dollar(char *content, int *start)
{
  //NOTE: cette fonction permet de crer un bloc jusqu'au prochain dollar.
  //il prend en compte les doubles quotes et ne va pas expandre dans les 
  //double quotes. Cette fonction s'utilise avant de split le content.
  int end;
  char  quote;
  char  *second_block;

  end = *start;
  quote = 'a';
  while (content[end] != '$' && content[end] != 0)
  {
    //NOTE: tant qu'on est pas sur un $, single or double quote, on avance dans
    //la string
    while (content[end] != '$' && content[end] != '"' && content[end] != '\'')
      end++;

    //NOTE: si on tombe sur une entree de quote, on va avancer jusqu'a la 
    //fermeture de quote. sa permet de skip les potentielles expansion s'y
    //trouvant.
    if (content[end] == '"' || content[end] == '\'')
    {
      quote = content[end];
      end++;
      while (content[end] != quote)
        end++;
      end++;
    }
  }
  second_block = ft_substr(content, *start, end - (*start));
  *start = end;
  return (second_block);
}

char  *go_until_quote(char *content, int *start)
{
  //NOTE: cette fonction permet de creer un bloc qui va jusqu'au prochain quote

  int end;
  char  *second_block;

  end = *start;
  while (content[end] != '"' && content[end] != '\'' && content[end] != 0)
    end++;
  second_block = ft_substr(content, *start, end - (*start));
  *start = end;
  return (second_block);
}

char  *expand_in_quote(t_data *data, char *row)
{
  //NOTE: cette fonction va expandre la current ligne du double tableau dans 
  //les quotes, apres avoir split le contenu de base
  char  *first_block;
  char  *second_block;
  int i;

  i = 0;
  first_block = ft_strdup("");
  while (row[i] != 0)
  {
    //NOTE: si le row[i] n'est pas un quote, alors on va creer
    //un bloc qui va jusqu'au prochain quote
    if (row[i] != '"' && row[i] != '\'')
      second_block = go_until_quote(row, &i);

    //NOTE: si le row[i] est un double or single quote, alors on va expandre ce 
      //qu'il y a dedans
    else if (row[i] == '"' || row[i] == '\'')
      second_block = quote_manager(data, row, &i, row[i]);

    //NOTE: meme principe, on va fusionner l'ancien bloc avec 
    //le nouveau
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

char  *expand_off_quote(t_data *data, char *content)
{
  //NOTE: cette fonction va expandre tout ce qui est hors des quotes

  char  *first_block;
  char  *second_block;
  int i;

  i = 0;
  first_block = ft_strdup("");
  while (content[i] != 0)
  {
    //NOTE: si le content[i] n'est pas un $, la fonction va creer
    //un bloc de ce point la jusqu'au prochain $
    if (content[i] != '$' && content[i] != 0)
      second_block = go_until_dollar(content, &i);

    //NOTE: si le content[i] est un $, la fonction va traiter le dollar,
      //et en faire un bloc
    else if (content[i] == '$')
      second_block = dollar_manager(data, content, &i, Q_NONE);

    //NOTE: ici on va fusionner le block precedant avec le bloc recent
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

char  **val_manager(char *content)
{
  //NOTE: c'est ici que va commencer l'expansion

  char  *temp;
  char  **splitted_content;
  int y;

  y = 0;

  //NOTE: il faut en premier expandre tout ce qui est hors des quotes
  temp = expand_off_quote(content);

  //NOTE: en deuxieme, il faut split le contenu separer par des espaces
  splitted_content = ft_split(temp, " ");
  free (temp);

  //NOTE: en troisieme, pour chaque "mot" (chaque ligne du double tableau),
  //il faut expandre ce qu'il y a dans les doubles quotes
  while (splitted_content[y] != NULL)
  {
    temp = ft_strdup(splitted_content[y]);
    free (splitted_content[y]);
    splitted_content[y] = expand_in_quote(temp);
    free (temp);
    y++;
  }
  return (splitted_content);
}
