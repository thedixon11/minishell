#include "../minishell_general.h"

void	init_signal_prompt(void)
{
	g_signal = 0;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

// NOTE: Le heredoc est lu avec read(), pas readline. Il faut sigaction.
void	init_signal_heredoc(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = signal_handler_heredoc;
	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

void	init_signal_parent(void)
{
	signal(SIGINT, signal_handler_exec);
	signal(SIGQUIT, signal_handler_exec);
}

void	init_signal_child(void)
{
	signal(SIGINT, signal_handler_exec);
	signal(SIGQUIT, SIG_DFL);
}
