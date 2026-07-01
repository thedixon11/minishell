#include "../minishell_general.h"

void  ft_error_child(t_data *data, t_bool do_i_perror, char *message, int code)
{
  if (code != 0 && do_i_perror == B_TRUE)
    perror(message);
  free_and_close_life(t_data *data)
  if (data->cmd_data != NULL)
   free_cmd_data(data->cmd_data);
  exit (code);
}
