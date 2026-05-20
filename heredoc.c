#include "minishell_xecution.h"

//TODO: pas du tout bien structurer, faut encore BEAUCOUP travailler dessus !

void  write_on_fd(t_line *heredoc)
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
		len_of_line = ft_strlen(line);
		write(heredoc->pipe_fd[1], line, len_of_line);
		free(line);
		line = get_next_line(STDIN_FILENO, heredoc->limiter, limiter_len);
		if (line == NULL)
			errors_exit(data, QUIT_HEREDOC, 0, 0);
	}
  free(line);
}

void create_heredoc_fd(t_line *heredoc)
{
  int *pipe_fd[2];

  pipe(pipe_fd);
  heredoc->pipe_fd = pipe_fd;
}

void  heredoc(t_data *data, t_line *line_cmd, t_env *env)
{
  t_line  *current;

  current = line_cmd;
  while (current != NULL)
  {
    if (current->type == L_HEREDOC)
    {
      create_heredoc_fd(current);
      write_on_fd(current);
    }
    current = current->next;
  }
}
