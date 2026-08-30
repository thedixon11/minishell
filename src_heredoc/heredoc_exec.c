/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:13:12 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:19:27 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

int	create_heredoc_fd(t_data *data, t_line *heredoc)
{
	if (pipe(data->heredoc_pipe_fds) == -1)
		return (error_int(data, I_PIPE, strerror(errno), 1));
	heredoc->fd = data->heredoc_pipe_fds[0];
	data->heredoc_pipe_fds[0] = -1;
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
	int	pid;

	error = 0;
	pid = 0;
	if (create_heredoc_fd(data, current) == 1)
		return (1);
	pid = fork();
	if (pid == -1)
		return (error_int(data, I_FORK, strerror(errno), 1));
	if (pid == 0)
		heredoc_child(data, current);
	heredoc_parent(data, &error);
	return (error);
}

int	heredoc_exec(t_data *data)
{
	int		error;
	t_line	*current;
	//int	number;

	error = 0;
	//number = 0;
	current = data->line_cmd;
	init_signal_heredoc();
	rl_event_hook = heredoc_event_hook;
	while (current != NULL && error == 0)
	{

		if (current->type == T_HEREDOC && error == 0)
		{
			// ft_printf("before heredoc n %d", number);
			// super_printer(data);
			error = heredoc_loop(data, current);
			//number++;
		}
		current = current->next;
	}
	init_signal_prompt();
	return (error);
}
