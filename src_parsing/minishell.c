#include "../minishell_general.h"

int	main()
{
	char	*line;
	t_token	*token;
	t_data	*data;

	data = data_creation();
	while (1)
	{
		line = readline("minishell$ ");	// -lreadline pour compil
		add_history(line);				// historique envoie au prompt fleche du haut et du bas pour check
		token = to_token(line);
		data->line_cmd = to_parse(data, token);
		execution_start(data);	
		// print_tokens(token);
		//print_lines(lines);
		if (!line)
			break ;						//renvoie NULL ctrl D to leave
	}
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

t_data	*data_creation(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);

	return (data);
}
