#include "minishell_xecution.h"

//TODO: pas du tout bien structurer, faut encore BEAUCOUP travailler dessus !
// IL FAUT QUE JIMPLEMENTE L'EXPANSION SA MERE

char  *go_until_dollar_hdoc(char *line, int *start)
{
  int end;

  end = *start;
  while (line[end] != '$' && line[end] != 0)
    end++;
  second_block = ft_substr(line, *start, end - (*start));
  return (second_block);
}

char  *expand_line(char *line, t_bool xpand_or_not)
{
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
  char  *line;
  char  *line_xpanded;
	int		limiter_len;
	int		len_of_line;

	limiter_len = ft_strlen(heredoc->content);
	line = get_next_line(STDIN_FILENO, heredoc->content, limiter_len);
	if (line_xpanded == NULL)
		errors_exit(data, QUIT_HEREDOC, 0, 0);
  line_xpanded = expand_line(line, xpand_or_not);
	while (ft_strncmp(line_xpanded, heredoc->content, limiter_len) != 0)
	{
		len_of_line = ft_strlen(line_xpanded);
		write(data->heredoc_pipe_fds[1], line_xpanded, len_of_line);
		free(line);
    free(line_xpanded);
		line = get_next_line(STDIN_FILENO, heredoc->content, limiter_len);
		if (line == NULL)
			errors_exit(data, QUIT_HEREDOC, 0, 0);
    line_xpanded = expand_line(line, xpand_or_not);
	}
  free(line);
  free (line_xpanded);
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
