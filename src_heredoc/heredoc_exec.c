#include "../minishell_general.h"

// NOTE: To create an heredoc, we cannot use functions like open, because we
// don't have a file to open. We need to do it by creating a pipe, which
// we'll write on it and creates us also a READ FD.
//
// NOTE: We have to store the fds in two places :
// 1) the WR_FD and RD_FD in data to use it in write_on_fd;
// 2) the RD_FD in the corresponding heredoc node;

int	create_heredoc_fd(t_data *data, t_line *heredoc)
{
	if (pipe(data->heredoc_pipe_fds) == -1)
		return (error_int(data, I_PIPE, strerror(errno), 1));
	heredoc->fd = data->heredoc_pipe_fds[0];
	return (0);
}

int	delimiter_manager_n_write_hdoc(t_data *data, t_line *current)
{
	char	*temp1;
	char	*temp2;

	temp1 = ft_strdup(current->content);
	if (!temp1)
		return (error_int(data, I_STRDUP, LIBFT_ERR, 1));
	ft_free((void **)&current->content);
	temp2 = expand_off_quote_hdoc(data, temp1);
	ft_free((void **)&temp1);
	if (!temp2)
		return (1);
	current->content = remove_n_xtract_quotes_hdoc(data, temp2);
	ft_free((void **)&temp2);
	if (!current->content)
		return (1);
	if (write_on_fd(data, current, B_FALSE) == 1)
		return (1);
	return (0);
}

int	heredoc_loop(t_data *data, t_line *current)
{
	int	error;
  int pid;
  int code;

	error = 0;
  pid = 0;
  code = 0;
	if (create_heredoc_fd(data, current) == 1)
		return (1);
  pid = fork();
  if (pid == 0)
  {
    ft_close_fd(&data->heredoc_pipe_fds[0]);
    data->do_i_exit = B_TRUE;
	  if ((ft_strchr(current->content, '\'') != NULL)
	  	|| (ft_strchr(current->content, '\"') != NULL))
	  	error = delimiter_manager_n_write_hdoc(data, current);
	  else
	  	error = write_on_fd(data, current, B_TRUE);
    code = data->code;
    free_and_close_life(data);
    exit (code);
  }
  ft_close_fd(&data->heredoc_pipe_fds[1]);
  wait_all_children(data);
  if (g_signal == SIGINT)
  {
	error = -1;
    handle_ctrl_c(data);    // BUG: 8
    init_signal_prompt();  // BUG: 9
  }
	return (error);
}

// NOTE: Here starts the heredocs executions. There is two steps per heredoc :
// 1) create a pipe for each heredoc(that creates fds);
// 2) if the delimiter has quotes, have to manage them;
// 2) write on that buffer, and store the read fd;

int	heredoc_exec(t_data *data)
{
	int		error;
	t_line	*current;

	error = 0;
	current = data->line_cmd;
	while (current != NULL && error == 0)
	{
		if (current->type == T_HEREDOC && error == 0)
			error = heredoc_loop(data, current);
		current = current->next;
	}
  init_signal_prompt();
	return (error);
}
