#include "../minishell_general.h"

int	g_signal;

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
    close(0);
}

t_data	*data_init(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
	{
		error_int(data, I_CALLOC, LIBFT_ERR, 1);
		exit(1);
	}
	return (data);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*token;
	t_data	*data;
	int	max_cmd_nb;
	int code;
	//int	y;

	(void) argv;
	(void) argc;
	//y = 0;
	code = 0;
	data = data_init();
	data->code = 0;
	data->max_cmd_nb = 0;
	data->line_cmd = NULL;
	data->env = create_env(envp);
	
	/*
	line = readline("minishell$ ");
	if (!line)
		exit(15);
	add_history(line);
	if (line[0] != 0)
	{
		token = to_token(line);
		if (token)
		{
			mini.line_cmd = to_parse(&max_cmd_nb, token);
			free_token_ll(token);
			mini.max_cmd_nb = max_cmd_nb;
			mini.code = execution_start(&mini);
		}
	}
	line = readline("minishell$ ");
	if (!line)
		exit(15);
	add_history(line);
	if (line[0] != 0)
	{
		token = to_token(line);

		if (token)
		{
			mini.line_cmd = to_parse(&max_cmd_nb, token); // BUG: debut bug
			free_token_ll(token);
			mini.max_cmd_nb = max_cmd_nb;
			mini.code = execution_start(&mini); // BUG: et bug du coup dans val manager
		}
	}*/

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		add_history(line);
		if (line[0] != 0)
		{
			token = to_token(line);
			if (!token)
				continue ;
			data->line_cmd = to_parse(&max_cmd_nb, token);
			free_token_ll(token);
			data->max_cmd_nb = max_cmd_nb;
			execution_start(data);
		}
	}
	data->do_i_exit = B_TRUE;
  code = data->code;
	free_and_close_life(data);
	return (code);
}

int	print_env(t_env	*env)
{
	printf("EH OUI VOILA L'ENV\n");
	while (env != NULL)
	{
		printf("%s = %s\n", env->name, env->content);
		env = env->next;
	}
	printf("\n\n");
	return (0);
}

int	print_tokens(t_token *token)
{
	while (token != NULL)
	{
		printf("value = %s, et type = %u\n", token->value, token->type);
		token = token->next;
	}
	return (0);
}

int	print_lines(t_line *lines)
{
	while (lines != NULL)
	{
		printf("content = %s, type = %d, et cmd = %d\n", lines->content, lines->type, lines->cmd_nb);
		lines = lines->next;
	}
	return (0);
}

void	free_token_ll(t_token *token)
{
	t_token	*current;

	if (!token)
		return ;
	current = token;
	while (current->next != NULL)
	{
		if (current->value != NULL)
			ft_free((void **)&current->value);
		current = current->next;
		ft_free((void **)&current->prev);
	}
	if (current->value != NULL)
		ft_free((void **)&current->value);
	ft_free((void **)&current);
	}
