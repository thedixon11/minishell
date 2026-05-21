#include "minishell_xecution.h"

//TODO: pas du tout bien structurer, faut encore BEAUCOUP travailler dessus !

int patch_input(t_data *data, t_line *line_cmd, t_env *env)
{
  
}

void  child_process(t_data *data, t_line *line_cmd, t_env *env, int current_cmd)
{
  int input;
  int output;
  t_line  *current;

  input = 0;
  output = 0;
  current = line_cmd;
  while (current->cmd_nb == current_cmd) 
  {
    if (current->type == T_INPUT)
      patch_input(data, line_cmd, env);
    if (current->type == T_OUTPUT)
      patch_output(data, line_cmd, env)
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
