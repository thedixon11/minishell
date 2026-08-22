#include "../minishell_general.h"

int    g_signal;

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

void	line_reader_and_exec(t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
    {
      init_signal_prompt();
			continue ;
    }
		add_history(line);    // WARNING: simon a sa mais dans le tokenizer
		if (line[0] != 0)
		{
			if (to_token(line, data) == 1)
				continue ;
			if (control_token_line(data) == 1)
				continue ;
			if (to_parse(data) == 1)
				continue ;
			handle_ctrl_c(data);      // BUG:   3
      init_signal_prompt();     // BUG:   4
			free_token_ll(&data->token_head);
			execution_start(data);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		code;

	(void)argv;
	if (argc > 1)
		return (error_no_data(I_MINISHELL, MINI_ARGS, 1));
  init_signal_prompt();     // BUG:   1
	code = 0;
	//rl_variable_bind("enable-bracketed-paste", "off");
	data = data_init();
	initialize_env(data, envp);
	line_reader_and_exec(data);
	data->do_i_exit = B_TRUE;
	code = data->code;
	free_and_close_life(data);
	return (code);
}
