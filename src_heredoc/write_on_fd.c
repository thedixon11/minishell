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

char	*create_line(t_data *data, t_line *heredoc, t_bool xpand_or_not, int *error)
{
	char	*line;
	char	*line_xpanded;

	line = readline("> ");
	if (g_signal == SIGINT)
	{
    //write(data->heredoc_pipe_fds[1], "\n", 1);
		return (ft_free((void **)&line), *error = -1, NULL);  // WARNING: voir si il faut que je backslash ou pas
	}
	if ((!line) || (ft_strncmp(line, heredoc->content, data->limiter_len) == 0))
	{
		//write(data->heredoc_pipe_fds[1], "\n", 1);
		return (ft_free((void **)&line), NULL); // WARNING: a confirmer
	}
	if (xpand_or_not == B_FALSE)
		return (line);
	line_xpanded = expand_line_hdoc(data, line);
	ft_free((void **)&line);
	if (!line_xpanded)
		return (*error = -1, NULL);  // WARNING: voir si il faut que je backslash ou pas
	return (line_xpanded);
}

// NOTE: The write_on_fd will write the STDIN_FILENO input in the pipe by
// using the WRITING FD of the heredoc pipe. Before writing on the fd, we have
// to expend the content inside.
int	write_on_fd(t_data *data, t_line *heredoc, t_bool xpand_or_not)
{
	char	*line;
	int		len_of_line;
	int error;

	error = 0;
	init_signal_heredoc();    // BUG:   5
	rl_event_hook = heredoc_event_hook;   // BUG:   6
	data->limiter_len = ft_strlen(heredoc->content) + 1;
	while (1)
	{
		line = create_line(data, heredoc, xpand_or_not, &error);
		if (!line || error == -1)    // BUG: 10
			break ;
		len_of_line = ft_strlen(line);
		error = write(data->heredoc_pipe_fds[1], line, len_of_line);
		if (error != -1)
		error = write(data->heredoc_pipe_fds[1], "\n", 1);
		if (error == -1)
		{
			error_int(data, I_WRITE, strerror(errno), 1);
			break ;
		}
	}
	ft_free((void **)&line);
	ft_close_fd(&data->heredoc_pipe_fds[1]);
	if (error == -1 || g_signal == SIGINT)
		return (1);
	return (0);
}
