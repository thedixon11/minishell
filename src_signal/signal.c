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

//INFO: rl_done = 1, set the end of readline process
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
	write(STDOUT_FILENO, "\n", 1);
}
