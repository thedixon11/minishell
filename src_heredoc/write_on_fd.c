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

char	*read_heredoc_line(t_data *data)
{
	char	buf[2];
	char	*line;
	char	*tmp;
	int		ret;

	line = ft_strdup("");
	if (!line)
		return (error_char(data, I_STRDUP, LIBFT_ERR, 1));
	buf[1] = 0;
	write(STDOUT_FILENO, "> ", 2);
	ret = read(STDIN_FILENO, buf, 1);
	while (ret == 1 && buf[0] != '\n')
	{
		tmp = line;
		line = ft_strjoin(tmp, buf);
		ft_free((void **)&tmp);
		if (!line)
			return (error_char(data, I_STRJOIN, LIBFT_ERR, 1));
		ret = read(STDIN_FILENO, buf, 1);
	}
	if (ret == 1 || (ret == 0 && line[0] != 0))
		return (line);
	if (ret == 0)
		write(STDOUT_FILENO, "\n", 1);
	return (ft_free((void **)&line), NULL);
}

char	*create_line(t_data *data, t_line *hdoc, t_bool xpand, int *error)
{
	char	*line;
	char	*line_xpanded;

	line = read_heredoc_line(data);
	if (g_signal == SIGINT)
		return (ft_free((void **)&line), *error = -1, NULL);
	if ((!line) || (ft_strncmp(line, hdoc->content, data->limiter_len) == 0))
		return (ft_free((void **)&line), NULL);
	if (xpand == B_FALSE)
		return (line);
	line_xpanded = expand_line_hdoc(data, line);
	ft_free((void **)&line);
	if (!line_xpanded)
		return (*error = -1, NULL);
	return (line_xpanded);
}

// NOTE: write_hdoc_line ecrit une ligne dans le pipe du heredoc, puis la
// libere. Retourne -1 en cas d'erreur d'ecriture, 0 sinon.

static int	write_hdoc_line(t_data *data, char *line)
{
	int	error;

	error = write(data->heredoc_pipe_fds[1], line, ft_strlen(line));
	if (error != -1)
		error = write(data->heredoc_pipe_fds[1], "\n", 1);
	ft_free((void **)&line);
	if (error == -1)
	{
		error_int(data, I_WRITE, strerror(errno), 1);
		return (-1);
	}
	return (0);
}

// NOTE: The write_on_fd will write the STDIN_FILENO input in the pipe by
// using the WRITING FD of the heredoc pipe. Before writing on the fd, we have
// to expend the content inside.
int	write_on_fd(t_data *data, t_line *heredoc, t_bool xpand)
{
	char	*line;
	int		error;

	error = 0;
	data->limiter_len = ft_strlen(heredoc->content) + 1;
	while (1)
	{
		line = create_line(data, heredoc, xpand, &error);
		if (!line || error == -1)
			break ;
		error = write_hdoc_line(data, line);
		if (error == -1)
			break ;
	}
	ft_close_fd(&data->heredoc_pipe_fds[1]);
	if (error == -1 || g_signal == SIGINT)
		return (1);
	return (0);
}
