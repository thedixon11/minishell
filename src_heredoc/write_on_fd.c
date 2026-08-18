#include "../minishell_general.h"

// NOTE: expand_line_hdoc will expand the STDIN_FILENO input content
// before writing it in the READ FD if xpand_or_not is TRUE. Otherwise, it
// will just strdup the line.

char	*expand_line_hdoc(t_data *data, char *line)
{
	char	*first;
	char	*second;
	int		i;

	i = 0;
	first = ft_strdup("");
	if (!first)
		return (error_char(data, I_STRDUP, LIBFT_ERR, 1));
	while (line[i] != 0)
	{
		if (line[i] != 0 && line[i] != '$')
			second = go_until_dollar_hdoc(data, line, &i);
		else if (line[i] != 0 && line[i] == '$')
			second = dollar_manager(data, line, &i, Q_HEREDOC);
		if (second != NULL)
			first = fusion_first_second_block(data, first, second);
		else
		{
			ft_free((void **)&first);
			return (NULL);
		}
	}
	return (first);
}

char	*create_line(t_data *data, t_line *heredoc, t_bool xpand_or_not)
{
	char	*line;
	char	*line_xpanded;

	if (write(STDOUT_FILENO, "> ", 2) == -1)
		return (error_char(data, I_WRITE, strerror(errno), 1));
	line = get_next_line(STDIN_FILENO, heredoc->content, data->limiter_len);
	if (g_signal == SIGINT)
		return (NULL);
	if (line == NULL)
		return (error_char(data, I_GNL, LIBFT_ERR, 1));
	if (ft_strncmp(line, heredoc->content, data->limiter_len) == 0)
		return (line);
	if (xpand_or_not == B_FALSE)
		return (line);
	line_xpanded = expand_line_hdoc(data, line);
	ft_free((void **)&line);
	if (!line_xpanded)
		return (NULL);
	return (line_xpanded);
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
	int		len_of_line;

	signal(SIGINT, handle_sigint_heredoc);
	data->limiter_len = ft_strlen(heredoc->content);
	line = create_line(data, heredoc, xpand_or_not);
	if (!line)
		return (1);
	while (ft_strncmp(line, heredoc->content, data->limiter_len) != 0)
	{
		len_of_line = ft_strlen(line);
		if (write(data->heredoc_pipe_fds[1], line, len_of_line) == -1)
		{
			error_int(data, I_WRITE, strerror(errno), 1);
			return (ft_free((void **)&line), 1);
		}
		ft_free((void **)&line);
		line = create_line(data, heredoc, xpand_or_not);
		if (!line)
			return (1);
	}
	signal(SIGINT, handle_sigint);
	ft_free((void **)&line);
	ft_close_fd(&data->heredoc_pipe_fds[1]);
	return (0);
}
