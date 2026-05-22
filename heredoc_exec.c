#include "minishell_xecution.h"

//TODO: pas du tout bien structurer, faut encore BEAUCOUP travailler dessus !

void  write_on_fd(t_data *data, t_line *heredoc)
{
  char	*line;
	int		limiter_len;
	int		len_of_line;

	limiter_len = ft_strlen(heredoc->limiter);
	line = get_next_line(STDIN_FILENO, heredoc->limiter, limiter_len);
	if (line == NULL)
		errors_exit(data, QUIT_HEREDOC, 0, 0);
	while (ft_strncmp(line, heredoc->limiter, limiter_len) != 0)
	{
    //TODO: il faut rajouter l'expansion de la line ici !!!
		len_of_line = ft_strlen(line);
		write(data->heredoc_pipe_fds[1], line, len_of_line);
		free(line);
		line = get_next_line(STDIN_FILENO, heredoc->limiter, limiter_len);
		if (line == NULL)
			errors_exit(data, QUIT_HEREDOC, 0, 0);
	}
  free(line);
  close(data->heredoc_pipe_fds[1]);
}

void create_heredoc_fd(t_data *data, t_line *heredoc)
{
  int *heredoc_pipe_fds[2];

  pipe(heredoc_pipe_fds);
  data->heredoc_pipe_fds = heredoc_pipe_fds;
}

void  heredoc_exec(t_data *data, t_line *line_cmd)
{
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
