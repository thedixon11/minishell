#include "../minishell_general.h"
#include "minishell_xecution.h"

// NOTE: go_until_dollar_hdoc will create a block until the 
// next dollar. It's an util of expand_line_hdoc.

char  *go_until_dollar_hdoc(char *line, int *start)
{
	int	end;
	char	*second_block;

	end = *start;
	while (line[end] != 0 && line[end] != '$')
		end++;
	second_block = ft_substr(line, *start, end - (*start));
	if (!second_block)
		return (ft_error_parent(B_TRUE, "malloc", 1));
	*start = end;
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
	{
		first_block = ft_strdup(line);
		return (first_block);
	}
	first_block = ft_strdup("");
	if (!first_block)
		return(ft_error_parent(B_TRUE, "malloc", 1));
	while (line[i] != 0)
	{
		if (line[i] != 0 && line[i] != '$')
			second_block = go_until_dollar_hdoc(line, &i);
		else if (line[i] != 0 && line[i] == '$')
			second_block = dollar_manager(data, line, &i, Q_HEREDOC);
		if (second_block != NULL)
		{
			temp = first_block;
			first_block = ft_strjoin(temp, second_block);
			data->saved_errno = errno;
			free(second_block);
			free(temp);
			errno = data->saved_errno
			if (!first_block)
				return (ft_error_parent(B_TRUE, "malloc", 1));
		}
		else 
		{
			free (first_block);
			return (NULL);
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

int	write_on_fd(t_data *data, t_line *heredoc, t_bool xpand_or_not)
{
	char	*line;
	char	*line_xpanded;
	int		limiter_len;
	int		len_of_line;

	limiter_len = ft_strlen(heredoc->content);
	line = get_next_line(STDIN_FILENO, heredoc->content, limiter_len);
	if (line == NULL)
		return (ft_error_parent_int(B_TRUE, "malloc", 1));
	line_xpanded = expand_line_hdoc(data, line, xpand_or_not);
	free(line);
	if (!line_xpanded)
		return (1);
	while (ft_strncmp(line_xpanded, heredoc->content, limiter_len) != 0)
	{
		len_of_line = ft_strlen(line_xpanded);
		data->error = write(data->heredoc_pipe_fds[1], line_xpanded,
				len_of_line);
		data->saved_errno = errno;
		free(line_xpanded);
		if (data->error != 0)
			return (ft_error_parent_int(B_TRUE, "write", 1));
		line = get_next_line(STDIN_FILENO, heredoc->content, limiter_len);
		if (line == NULL)
			return (ft_error_parent_int(B_TRUE, "malloc", 1));
		line_xpanded = expand_line_hdoc(data, line, xpand_or_not);
		free(line);
		if (!line_xpanded)
			return (1);
	}
	free(line);
	free(line_xpanded);
	close(data->heredoc_pipe_fds[1]);
	return (0);
}

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
		return (ft_error_parent_int(B_TRUE, "pipe", 1));
	heredoc->fd = data->heredoc_pipe_fds[0];
	temp = ft_strdup(heredoc->content);
	if (!temp)
		return (ft_error_parent_int(B_TRUE, "malloc", 1));
	heredoc->content = ft_strjoin(temp, "\n");
	data->saved_errno = errno;
	free(temp);
	if (!heredoc->content)
		return (ft_error_parent_int(B_TRUE, "malloc", 1));
	return (0);
}

// NOTE: Here starts the heredocs executions. There is two steps per heredoc :
// 1) create a pipe for each heredoc(that creates fds);
// 2) if the delimiter has quotes, have to manage them;
// 2) write on that buffer, and store the read fd;

int	heredoc_exec(t_data *data)
{
	t_line	*current;
	char	*temp;

	current = data->line_cmd;
	while (current != NULL)
	{
		if (current->type == T_HEREDOC)
		{
			if (create_heredoc_fd(data, current) == 1)
				return (1);
			if (ft_strchr(current->content, '\'') == NULL
					&& ft_strchr(current->content, '"') == NULL)
				write_on_fd(data, current, B_TRUE);
			else
			{
				temp = ft_strdup(current->content);
				if (!temp)
					ft_error_parent_int(B_TRUE, "malloc", 1);
				current->content = delimiter_manager_hdoc(data, temp);
				free(temp);
				if (!current->content)
					return (1);
				write_on_fd(data, current, B_FALSE);
			}
		}
		current = current->next;
	}
	return (0);
}
