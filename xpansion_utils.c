#include "minishell_xpansion.h"

t_bool is_it_dollar_or_quote(char c, t_quote q_mode)
{
  if (c == '$')
    return (B_TRUE);
  else if (c == '"' && q_mode == Q_NONE)
    return (B_TRUE);
  else if (c == '\'' && q_mode == Q_NONE)
    return (B_TRUE);
  else
    return (B_FALSE);
}

char  *second_block_not_dollar_or_quote(char *str, int *i, t_quote q_mode)
{
  //NOTE: str peut etre soit value soit inside_quote
  //i peut etre soit i_value soit i_quote

  int end;
  int len;
  char  *second_block;

  end = *i;
  len = 0;
  while (is_it_dollar_or_quote(str[end], q_mode) == B_FALSE && str[end] != 0)
    end++;
  len = end - *i;
  second_block = ft_substr(str, *i, len);
  *i = end;
  return (second_block);
}
