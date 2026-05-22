#include "minishell_xecution.h"

//TODO: pas du tout bien structurer, faut encore BEAUCOUP travailler dessus !


void  child_process(t_data *data, t_line *line_cmd, t_env *env, int current_cmd)
{
  t_line  *current;
  t_cmd *cmd_data;

  current = line_cmd;
  close(data->pipe_fd[0]);
  while (current->cmb_nb != current_cmd && current != NULL)
    current = current->next;
  while (current->cmd_nb == current_cmd && current != NULL)
  {
    if (current->type == T_PIPE_IN || current->type == T_INPUT || current->type == T_HEREDOC)
      dup2(current->fd, STDIN_FILENO);
    else if (current->type == T_OUTPUT_APPEND || current->type == T_OUTPUT_TRUNC || current->type == T_PIPE_IN)
      dup2(current->fd, STDOUT_FILENO);
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

void  open_fd_in_line_cmd(t_data *data, t_line *line_cmd, int current_cmd)
{
  t_line  *current;

  current = line_cmd;
  while(current->cmd_nb != current_cmd && current != NULL)
    current = current->next;
  while (current->cmd_nb == current_cmd && current != NULL)
  {
    if (current->type == T_PIPE_IN)
      current->fd = data->old_read_fd;
    else if (current->type == T_INPUT)
      current->fd = open(current->content, O_RDONLY);
    else if (current->type == T_HEREDOC)
      current->fd = data->heredoc_pipe_fds[0];
    else if(current->type == T_OUTPUT_APPEND)
      current->fd = open(current->content, O_WRONLY | O_CREAT
				| O_APPEND, 0644);
    else if(current->type == T_OUTPUT_TRUNC)
		  outfile = open(data->argv[y + 1], O_WRONLY
				| O_CREAT | O_TRUNC, 0644);
    else if (current->type == T_PIPE_OUT)
      current->fd = data->pipe_fd[1];
    current = current->next;
  }
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
    open_fd_in_line_cmd(data, line_cmd);
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
