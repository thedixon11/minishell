#include "minishell_xecution.h"

char  *go_until_dollar_hdoc(char *line, int *start)
{
  //NOTE: la fonction qui va creer le block jusqu'au dollar
  //
  int end;

  end = *start;
  while (line[end] != '$' && line[end] != 0)
    end++;
  second_block = ft_substr(line, *start, end - (*start));
  return (second_block);
}

char  *expand_line_hdoc(char *line, t_bool xpand_or_not)
{
  //NOTE: la fonction qui va expand la line lue dans gnl avant de l'ecrire sur le fd
  //
  char  *first_block;
  char  *second_block;
  int y;

  i = 0;
  if (xpand_or_not == B_TRUE)
    return (ft_strdup(line));
  first_block = ft_strdup("");
  while (line[i] != 0)
  {
    if (line[i] != '$' && line[i] != 0)
      second_block = go_until_dollar_hdoc(line, &i);
    else if (line[i] == '$' && line[i] != 0)
      second_block = dollar_manager(data, line, &i, Q_HEREDOC);
    if (second_block != NULL)
    {
      temp = first_block;
      first_block = ft_strjoin(temp, second_block);
      free(second_block);
      free(temp);
    }
  }
return (first_block);
}

void  write_on_fd(t_data *data, t_line *heredoc, t_bool xpand_or_not)
{
  //NOTE: la fonction qui va ecrire sur le fd du heredoc

  char  *line;
  char  *line_xpanded;
	int		limiter_len;
	int		len_of_line;

	limiter_len = ft_strlen(heredoc->content) + 1;

  //WARNING: faut faire attention a bien inclure le gnl qui prend en compte 
  // un delimiter dans la libft !!!
	line = get_next_line(STDIN_FILENO, heredoc->content, limiter_len);
	if (line == NULL)
		errors_exit(data, QUIT_HEREDOC, 0, 0);

  line_xpanded = expand_line_hdoc(line, xpand_or_not);
	while (ft_strncmp(line_xpanded, heredoc->content, limiter_len) != 0)
	{
		len_of_line = ft_strlen(line_xpanded);
		write(data->heredoc_pipe_fds[1], line_xpanded, len_of_line);
		free(line);
    free(line_xpanded);

    //WARNING: faut faire attention a bien inclure le gnl qui prend en compte 
    // un delimiter dans la libft !!!
		line = get_next_line(STDIN_FILENO, heredoc->content, limiter_len);
		if (line == NULL)
			errors_exit(data, QUIT_HEREDOC, 0, 0);

    line_xpanded = expand_line_hdoc(line, xpand_or_not);
	}
  free(line);
  free (line_xpanded);
  close(data->heredoc_pipe_fds[1]);
}

void create_heredoc_fd(t_data *data, t_line *heredoc)
{
  //NOTE: pour creer un fd pour le heredoc, on ne peut pas utiliser des fonctions 
  //tels que open, vu qu'on a pas de fichier. On va pour ca creer un pipe, cad un 
  //buffer dans lequel on va y ecrire le contenu dedans et qui va gener le fd necessaire.

  int *heredoc_pipe_fds[2];

  pipe(heredoc_pipe_fds);
  data->heredoc_pipe_fds = heredoc_pipe_fds;
}

void  heredoc_exec(t_data *data, t_line *line_cmd)
{
  //NOTE: ici commence l'execution de tous les heredocs. on doit :
  //1) creer un fd pour le heredoc;
  //2) ecrire sur ce fd;

  t_line  *current;

  current = line_cmd;
  while (current != NULL)
  {
    if (current->type == T_HEREDOC)
    {
      create_heredoc_fd(data, current);
      write_on_fd(data, current);
    }
    current = current->next;
  }
}
