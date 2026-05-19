#include "minishell_xecution.h"

//TODO: pas du tout bien structurer, faut encore BEAUCOUP travailler dessus !

void  write_on_fd()
{
  char	*line;
	int		limiter_len;
	int		len_of_line;

	close(data->pipe_fd[0]);
	limiter_len = ft_strlen(data->limiter);
	line = get_next_line(STDIN_FILENO, data->limiter, limiter_len);
	if (line == NULL)
		errors_exit(data, QUIT_HEREDOC, 0, 0);
	while (ft_strncmp(line, data->limiter, limiter_len) != 0)
	{
		len_of_line = ft_strlen(line);
		write(data->pipe_fd[1], line, len_of_line);
		free(line);
		line = get_next_line(STDIN_FILENO, data->limiter, limiter_len);
		if (line == NULL)
			errors_exit(data, QUIT_HEREDOC, 0, 0);
	}
	free(line);
	close(data->pipe_fd[1]);
	close_all_fd(data);
	free_all(data);
	exit(0);

}

t_heredoc *create_heredoc_fd(int heredoc_num, int block_num)
{
  t_heredoc *new_node;
  int *pipe_fd[2];

  pipe(pipe_fd);
  new_node = ft_calloc(1, sizeof(t_heredoc));
  new_node->heredoc_num = heredoc_num;
  new_node->pipe_fd = pipe_fd;
  new_node->block_num = block_num;
  return (new_node);
}

void  heredoc(t_data *data, t_line *line_cmd, t_env *env)
{
  t_line  *current;
  t_heredoc *heredoc_linked_list;
  t_heredoc *new_node;
  int heredoc_num;

  heredoc_num = 0; 
  current = line_cmd;
  while (current != NULL)
  {
    if (current->type == L_HEREDOC)
    {
      new_node = create_heredoc_fd(heredoc_num, block_num);
      new_node = write_on_fd();
    }
    current = current->next;
    new_node = 
  }
}
