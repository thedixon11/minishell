#include "../minishell_general.h"

int    end_heredoc(char *line)
{
    if (line)
        ft_free((void **)&line);
    signal(SIGINT, handle_sigint);
    return (1);
}
void    setup_signals(void)
{
    g_signal = 0;
    signal(SIGINT, handle_sigint);
    signal(SIGQUIT, SIG_IGN);
}

void    handle_sigint(int sig)
{
    g_signal = sig;

    write(1, "\n", 1);
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

void    handle_sigint_heredoc(int sig)
{
    g_signal = sig;
    write(1, "\n", 1);
}

void	handle_sigint_exec(int sig)
{
	g_signal = sig;
    write(1, "\n", 1);
}

// BUG: signals on all that file
