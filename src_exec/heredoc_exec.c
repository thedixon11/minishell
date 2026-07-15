#include "../minishell_general.h"
#include "minishell_xecution.h"

// NOTE: To create an heredoc, we cannot use functions like open, because we
// don't have a file to open. We need to do it by creating a pipe, which
// we'll write on it and creates us also a READ FD.
//
// NOTE: We have to store the fds in two places :
// 1) the WR_FD and RD_FD in data to use it in write_on_fd;
// 2) the RD_FD in the corresponding heredoc node;

int	create_heredoc_fd(t_data *data, t_line *heredoc)
{
	char	*temp;

	if (pipe(data->heredoc_pipe_fds) == -1)
	{
		data->saved_errno = errno;
		return (ft_error_parent_int(data, PIPE_ERR, 1));
	}
	heredoc->fd = data->heredoc_pipe_fds[0];
	temp = ft_strdup(heredoc->content);
	data->saved_errno = errno;
	if (!temp)
		return (ft_error_parent_int(data, MALLOC_ERR, 1));
	heredoc->content = ft_strjoin(temp, "\n");
	data->saved_errno = errno;
	ft_free((void **)&temp);
	if (!heredoc->content)
		return (ft_error_parent_int(data, MALLOC_ERR, 1));
	return (0);
}

int	no_quotes_in_delimiter(t_data *data, t_line *current)
{
	char	*temp;

	temp = ft_strdup(current->content);
	data->saved_errno = errno;
	if (!temp)
		return (ft_error_parent_int(data, MALLOC_ERR, 1));
	current->content = delimiter_manager_hdoc(data, temp);
	ft_free((void **)&temp);
	if (!current->content)
		return (1);
	if (write_on_fd(data, current, B_FALSE) == 1)
		return (1);
	return (0);
}

// NOTE: Here starts the heredocs executions. There is two steps per heredoc :
// 1) create a pipe for each heredoc(that creates fds);
// 2) if the delimiter has quotes, have to manage them;
// 2) write on that buffer, and store the read fd;

int	heredoc_exec(t_data *data)
{
	t_line	*current;

	current = data->line_cmd;
	while (current != NULL && data->error == 0)
	{
		if (current->type == T_HEREDOC && data->error == 0)
		{
			if (create_heredoc_fd(data, current) == 1)
				return (1);
			if (ft_strchr(current->content, '\'') == NULL
				&& ft_strchr(current->content, '"') == NULL)
				data->error = no_quotes_in_delimiter(data, current);
			else
				data->error = write_on_fd(data, current, B_TRUE);
		}
		current = current->next;
	}
	if (data->error != 0)
		return (1);
	return (0);
}
