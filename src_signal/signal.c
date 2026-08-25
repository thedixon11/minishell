/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:15:18 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:17:30 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

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

void	signal_handler_exec(int signo)
{
	if (signo == SIGINT)
		g_signal = SIGINT;
	else if (signo == SIGQUIT)
		g_signal = SIGQUIT;
	rl_on_new_line();
	rl_replace_line("", 0);
	write(STDOUT_FILENO, "\n", 1);
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
