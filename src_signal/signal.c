/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fducrot <fducrot@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/26 20:17:09 by fducrot           #+#    #+#             */
/*   Updated: 2026/08/26 20:18:54 by fducrot          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"
#include <unistd.h>

void	signal_handler(int signo)
{
	(void)signo;
	g_signal = SIGINT;
	write(STDOUT_FILENO, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_handler_heredoc(int signo)
{
	(void)signo;
	g_signal = SIGINT;
}

void	handle_ctrl_c(t_data *data)
{
	if (g_signal == 2)
	{
		data->code = (128 + g_signal);
		g_signal = 0;
	}
}

void	report_signaled_child(t_data *data, int status)
{
	int	signal;

	signal = WTERMSIG(status);
	if (signal == SIGINT)
		write(STDERR_FILENO, "\n", 1);
	else if (signal == SIGQUIT)
		write(STDERR_FILENO, "Quit (core dumped)\n", 19),
	data->code = 128 + signal;
}

void	handle_ctrl_d(t_data *data)
{
	int	code;

	code = data->code;
	write(STDERR_FILENO, "exit\n", 5);
	data->do_i_exit = B_TRUE;
	free_and_close_life(data);
	exit(code);
}
