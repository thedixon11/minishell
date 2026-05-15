
#ifndef ALEX_H
# define ALEX_H
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_type				// definition du type de chaq token
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	REDIR_APPEND
}					t_type;

typedef struct s_token			//liste chainee des tokens
{
	char			*value;		// caracetere(s) du token
	t_type			type;		// enum type du token
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_state			//memoire de l'avancee pendant la tokenisation
{
	char			*str; 		//string transmis dans le prompt
	int				i;			//place dans la string
	char			quote;		//quote = \0 si simple = ' si double = "
	struct s_token	*current;	//token en cours
	struct s_token	*head;		//tete de la liste
}					t_state;

#endif