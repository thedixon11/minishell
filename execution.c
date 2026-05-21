#include "minishell_xecution.h"

//TODO: pas du tout bien structurer, faut encore BEAUCOUP travailler dessus !

int patch_input(t_data *data, t_line *line_cmd, t_env *env, t_line *current)
{
  dup2(current->fd, STDIN_FILENO);
}

void  child_process(t_data *data, t_line *line_cmd, t_env *env, int current_cmd)
{
  t_line  *current;

  current = line_cmd;
  close(data->pipe_fd[0]);
  while (current->cmd_nb == current_cmd || current != NULL) 
  {
    if (current->type == T_PIPE_IN || current->type == T_INPUT)
      patch_input(data, line_cmd, env, current);
    if (current->type == T_OUTPUT)
      patch_output(data, line_cmd, env);
    current = current->next;
  }


}

void	parent_process(t_data *data, int current_cmd)
{
	if (current_cmd > 0)
		close(data->old_read_fd);
	if (current_cmd <= data->max_cmd)
	{
		data->old_read_fd = data->pipe_fd[0];

    //NOTE: je dois revoir a quoi sert ce if
		if (data->do_i_wait == 1)
		{
			wait(NULL);
			data->do_i_wait = 0;
		}

		close(data->pipe_fd[1]);
	}
	data->y++;
}

void	execute_cmds(t_data *data, t_line *line_cmd, t_env *env)
{
	int	pid;
  int current_cmd;

	current_cmd = 0;
	while (current_cmd <= data->max_cmd)
	{
		if (pipe(data->pipe_fd) == -1)
				errors_exit(data, PIPE_ERR, 0, 0);
		pid = fork();
		if (pid == -1)
			errors_exit(data, FORK_ERR, 0, 0);
		if (pid == 0)
			child_process(data, line_cmd, env, current_cmd);
		if (pid > 0)
			parent_process(data, current_cmd);
	}
	while (wait(NULL) > 0)
		;
	if (data->old_read_fd >= 0)
		close(data->old_read_fd);
}

void  *execution(t_data *data, t_line *line_cmd, t_env *env)
{
  heredoc_exec(line_cmd);
  execute_cmds(data, line_cmd, env);
  close_all_fd();
  free_all();
}
