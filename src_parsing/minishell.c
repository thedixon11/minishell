#include "../minishell_general.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_token	*token;
	t_line	*line_cmd;
	int		max_cmd_nb;
	t_env	*env;
	int		code;

	(void) argv;
	(void) argc;
	code = 0;
	env = create_env(envp);
	line = readline("minishell$ ");	// -lreadline pour compil
	add_history(line);				// historique envoie au prompt fleche du haut et du bas pour check
	token = to_token(line);
	line_cmd = to_parse(&max_cmd_nb, token);
	code = execution_start(line_cmd, max_cmd_nb, env, code);
	free_token_ll(token);
	/*
	while (1)
	{
		line = readline("minishell$ ");	// -lreadline pour compil
		add_history(line);				// historique envoie au prompt fleche du haut et du bas pour check
		token = to_token(line);
		line_cmd = to_parse(&max_cmd_nb, token);
		code = execution_start(line_cmd, max_cmd_nb, env, code);	
		// print_tokens(token);
		//print_lines(lines);
		if (!line)
			break ;						//renvoie NULL ctrl D to leave
	}*/
		return (0);
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
	t_token	*to_delete;

	current = token;
	current = current->next;
	while (current->next != NULL)
	{
		to_delete = current->prev;
		ft_free((void **)&to_delete->value);
		ft_free((void **)&to_delete);
		current = current->next;
	}
	to_delete = current->prev;
	ft_free((void **)&to_delete->value);
	ft_free((void **)&to_delete);
	ft_free((void **)&current->value);
	ft_free((void **)&current);
}
