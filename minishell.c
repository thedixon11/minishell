#include "alex.h"

int	main()
{
	char	*line;
	t_token	*token;

	while (1)
	{
		line = readline("minishell$ ");	// -lreadline pour compil
		add_history(line);				// historique envoie au prompt fleche du haut et du bas pour check
		token = to_token(line);
		print_tokens(token);
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