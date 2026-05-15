#include "alex.h"

int	main()
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");	// -lreadline pour compil
		add_history(line);				// historique envoie au prompt fleche du haut et du bas pour check
		to_token(line);
		if (!line)
			break ;						//renvoie NULL ctrl D to leave
	}
		return (0);
}