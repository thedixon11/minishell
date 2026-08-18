#include "../minishell_general.h"

t_data	*data_init(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
	{
		error_int(data, I_CALLOC, LIBFT_ERR, 1);
		exit(1);
	}
	data->code = 0;
	data->max_cmd_nb = 0;
	data->line_cmd = NULL;
	data->do_i_exit = B_TRUE;
	return (data);
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
    g_signal = SIGINT;
    close(0);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*token;
	t_data	*data;
	int	max_cmd_nb;
	int code;

	(void) argv;
	if (argc > 1)
		return (error_no_data(I_MINISHELL, MINI_ARGS, 1));
	code = 0;
	data = data_init();
	initialize_env(data, envp);
	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		if (line[0] != 0)
		{
			token = to_token(line, data);
			if (!token)
				continue ;
			to_parse(data, token);
			free_token_ll(token);
			execution_start(data);
		}
	}
	data->do_i_exit = B_TRUE;
	code = data->code;
	free_and_close_life(data);
	return (code);
}
