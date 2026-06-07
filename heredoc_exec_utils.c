#include "minishell_xecution.h"

// NOTE: will extract inside the quote

char  *extract_quote_hdoc(char *old_del, int *i, char quote)
{
  int end;
  char  *second_block;
  char  *inside_quote;

  (*start)++;
  end = *start;
  while (old_del[end] != quote)
    end++;
  inside_quote = ft_substr(old_del, *i, end - (*i));
  *i = end + 1;
  return (inside_quote);
}

// NOTE: will extract before quote entry;

char  *go_until_quote_hdoc(char *old_del, int *i)
{
  int end;
  char  *second_block;

  end = *start;
  while (old_del[end] != '\'' && old_del[end] != '\"'&& old_del[end] != NULL)
    end++;
  second_block = ft_substr(old_del, *start, end - (*start));
  *start = end;
  return (second_block);
}

// NOTE: delimiter manager will treat the quotes of the delimiter and removed them

char  *delimiter_manager_hdoc(char *old_del)
{
  char  *first_block;
  char  *second_block;
  char  *temp;
  int i;

  i = 0;
  first_block = ft_strdup("");
  while (old_del[i] != NULL)
  {
    if (old_del[i] != '\'' && old_del[i] != '\"' && old_del[i] != NULL)
      second_block = go_until_quote_hdoc(old_del, &i);
    else if (old_del[i] == '\'' || old_del[i] != '\"')
     second_block = extract_quote_hdoc(old_del, &i, old_del[i]);
    if (second_block != NULL)
    {
      temp = first_block;
      first_block = ft_strjoin(temp, second_block);
      free (temp);
      free(second_block);
    }
  }
  return (second_block);
}
