#include "minishell_xecution.h"

char  **expand_args_array(t_data *data, char **temp)
{
  char  **first_block;
  char  **second_block;
  int y;

  y = 0;
  while (temp[y] != NULL)
  {
   if (ft_strchr(temp[y], '"') == 0)
     
  }
}

char  **prepare_args_array(t_data *data, char *cmd_content)
{
  char  **temp;
  char **args_array;

  temp = ft_split_quotes(cmd_expanded, " ");
  args_array = expand_args_array(data, temp);
  return (args_array);
}

char  **prepare_args_array(t_data *data, char *cmd_content)
{
  char  *cmd_expanded;
  int y;

  cmd_expanded = value_manager(data, cmd_content);
  args_array = ft_split_quotes(cmd_expanded, " ");

  y = 0;
  args_array = ft_split_quotes(cmd_expanded, " ");

  return (args_array);
}
