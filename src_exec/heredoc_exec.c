#include "../minishell_general.h"

// NOTE: go_until_dollar_hdoc will create a block until the 
// next dollar. It's an util of expand_line_hdoc.

char  *go_until_dollar_hdoc(char *line, int *start)
{
	int	end;
	char	*second_block;

  end = *start;
  while (line[end] != '$' && line[end] != 0)
    end++;
  second_block = ft_substr(line, *start, end - (*start));
  return (second_block);
}

// NOTE: expand_line_hdoc will expand the STDIN_FILENO input content
// before writing it in the READ FD if xpand_or_not is TRUE. Otherwise, it
// will just strdup the line.

char  *expand_line_hdoc(t_data *data, char *line, t_bool xpand_or_not)
{
  char  *first_block;
  char  *second_block;
  char  *temp;
  int i;

  i = 0;
  if (xpand_or_not == B_FALSE)
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

// NOTE: The write_on_fd will write the STDIN_FILENO input in the pipe by
// using the WRITING FD of the heredoc pipe. Before writing on the fd, we have
// to expend the content inside.
//
// WARNING: We have to put the corrrect gnl in the libft !! The one that
// can manage a delimiter.

void  write_on_fd(t_data *data, t_line *heredoc, t_bool xpand_or_not)
{

  char  *line;
  char  *line_xpanded;
	int		limiter_len;
	int		len_of_line;

	limiter_len = ft_strlen(heredoc->content) + 1;
	line = get_next_line(STDIN_FILENO, heredoc->content, limiter_len);
	if (line == NULL)
		exit(10);

  line_xpanded = expand_line_hdoc(data, line, xpand_or_not);
	while (ft_strncmp(line_xpanded, heredoc->content, limiter_len) != 0)
	{
		len_of_line = ft_strlen(line_xpanded);
		write(data->heredoc_pipe_fds[1], line_xpanded, len_of_line);
		free(line);
		free(line_xpanded);
		line = get_next_line(STDIN_FILENO, heredoc->content, limiter_len);
		if (line == NULL)
			exit(10);

    line_xpanded = expand_line_hdoc(data, line, xpand_or_not);
	}
  free(line);
  free (line_xpanded);
  close(data->heredoc_pipe_fds[1]);
}

// NOTE: To create an heredoc, we cannot use functions like open, because we
// don't have a file to open. We need to do it by creating a pipe, which 
// we'll write on it and creates us also a READ FD.
//
// NOTE: We have to store the fds in two places :
// 1) the WR_FD and RD_FD in data to use it in write_on_fd;
// 2) the RD_FD in the corresponding heredoc node;

void create_heredoc_fd(t_data *data, t_line *heredoc)
{
	pipe(data->heredoc_pipe_fds);
	heredoc->fd = data->heredoc_pipe_fds[0];
}

// NOTE: Here starts the heredocs executions. There is two steps per heredoc :
// 1) create a pipe for each heredoc(that creates fds);
// 2) if the delimiter has quotes, have to manage them;
// 2) write on that buffer, and store the read fd;

void	heredoc_exec(t_data *data)
{
	t_line	*current;
  char  *temp;

	current = data->line_cmd;
	while (current != NULL)
	{
		if (current->type == T_HEREDOC)
		{
			create_heredoc_fd(data, current);
			if (ft_strchr(current->content, '\'') && ft_strchr(current->content, '"') == NULL)
			  write_on_fd(data, current, B_TRUE);
			else
      {
        temp = ft_strdup(current->content);
        current->content = delimiter_manager_hdoc(temp);
        free(temp);
				write_on_fd(data, current, B_FALSE);
      }
		}
		current = current->next;
	}
}
