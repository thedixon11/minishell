#include "../minishell_general.h"

void  ft_free(void **ptr)
{
  if (*ptr != NULL)
  {
    free(*ptr);
    *ptr = NULL;
  }
}

void  wait_all_children(t_data *data)
{
  int status;

  while (waitpid(-1, &status, 0) != -1)
  {
    if (WIFEXITED(status))
      data->exit_code = WEXITSTATUS(status);
    else if (WIFSIGNALED(status))
        data->exit_code = 128 + WTERMSIG(status);
  }
}

void	free_cmd_data(t_cmd *cmd_data)
{
	if (cmd_data->prog_fullname != NULL)
		ft_free(&cmd_data->prog_fullname);
	if (cmd_data->args_array != NULL)
		ft_free_tab(&cmd_data->args_array);
	if (cmd_data->path_array != NULL)
		ft_free_tab(&cmd_data->path_array);
	if (cmd_data->env != NULL)
		ft_free_tab(&cmd_data->env);
}

void	free_env(t_env *env)
{
	t_env	*current;

	current = env;
	while (current->next != NULL)
	{
		if (current->name != NULL)
			ft_free(&current->name);
		if (current->content != NULL)
			ft_free(&current->content);
		current = current->next;
		if (current->prev != NULL)
			ft_free(&current->prev);
	}
	if (current->name != NULL)
		ft_free(&current->name);
	if (current->content != NULL)
		ft_free(&current->content);
	ft_free(&current);
}

void	free_line_cmd(t_line *line_cmd)
{
	t_line	*current;

	current = line_cmd;
	while (current->next != NULL)
	{
		if (current->content != NULL)
			ft_free(&current->content);
		if (current->content_xpand != NULL)
			ft_free_tab(&current->content_xpand);
		current = current->next;
		ft_free(&current->prev);
	}
	if (current->content != NULL)
		ft_free(&current->content);
	if (current->content_xpand != NULL)
		ft_free_tab(&current->content_xpand);
	ft_free(&current);
}

void  close_fd(int *fd)
{
  if (*fd != -1)
  {
    close(*fd);
    *fd = -1;
  }
}

void	close_all_fd(t_line *line_cmd)
{
	t_line	*current;

	current = line_cmd;
	while (current != NULL)
	{
		if (current->fd > -1)
    {
			close(current->fd);
      current->fd = -1;
    }
		current = current->next;
	}
}

void	free_and_close_life(t_data *data)
{
	close_all_fd(data->line_cmd);
	free_line_cmd(data->line_cmd);
	free_env(data->env);
	ft_free(&data);
}
