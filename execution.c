#include "minishell_xecution.h"

//TODO: pas du tout bien structurer, faut encore BEAUCOUP travailler dessus !

void  child_process(t_data *data, t_line *line_cmd, int current_cmd)
{
  t_line  *current;
  t_cmd *cmd_data;

  current = line_cmd;

  //NOTE: le READ FD de l'enfant ne sert a rien on doit de toute facon le patcher
  close(data->pipe_fd[0]);

//NOTE: il faut aller vers la premiere node de la cmd dans laquelle on est
  while (current->cmb_nb != current_cmd && current != NULL)
    current = current->next;

  //NOTE: une fois arriver sur la premier node de la cmd correspondante, on va 
  //patcher dans l'ordre les input et les outputs avec dup2. Les derniers dup2 seront
  //nos input et outputs de l'execution
  while (current->cmd_nb == current_cmd && current != NULL)
  {
    if (current->type == T_PIPE_IN || current->type == T_INPUT || current->type == T_HEREDOC)
      dup2(current->fd, STDIN_FILENO);
    else if (current->type == T_OUTPUT_APPEND || current->type == T_OUTPUT_TRUNC || current->type == T_PIPE_IN)
      dup2(current->fd, STDOUT_FILENO);
    current = current->next;
  }

  //NOTE: une fois qu'on a patcher, on reviens au debut de la ligne de cmd et 
  //l'on va sur la node de type cmd qui va nous servir a la preparation de l'execution
  current = line_cmd;
  while (current->type != T_COMMAND && current->cmd_nb == current_cmd)
    current = current->next;

  //TODO: a continuer preparation de l'execution et utiliser execve et free
  cmd_data = execve_preparation(data, current->content);
  

}

void	parent_process(t_data *data, int current_cmd)
{
    //NOTE: la seule mission du parent est de recuperer le READ FD pour le redonner au 
    //prochain enfant

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
  //NOTE: ici on va remplir dans les nodes les fds correspondant
    //on va open les files input, output, etc.
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
   //NOTE: le choix est fait d'ouvrir tout les fds dans le parent avant de fork
   //au lieu de le faire dans l'enfant. Ce qui sera fait dans l'enfant sont juste
   //les dup2
    open_fd_in_line_cmd(data, line_cmd);

		pid = fork();
		if (pid == -1)
			errors_exit(data, FORK_ERR, 0, 0);
		if (pid == 0)
			child_process(data, line_cmd, env, current_cmd);
		if (pid > 0)
			parent_process(data, current_cmd);
	}
    //TODO: faudra remanager comment utiliser wait et waitpid
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
