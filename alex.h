
#ifndef ALEX_H
# define ALEX_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef struct s_command		//args 1 par commande entre pipe et struct redirection
{
	char				**args;
	int					index;
	struct s_command	*prev;
	struct s_command	*next;
	struct s_redir		*redir;
}						t_command;

typedef struct s_redir			// redir avec le file associe
{
	t_type			type;
	char			*file;
	struct s_redir	*prev;
	struct s_redir	*next;
}					t_redir;

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
	char			*value;		// caractere(s) du token
	t_type			type;		// enum type du token
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_state			//memoire de l'avancee pendant la tokenisation
{
	int				start;		// handle space
	char			*str; 		//string transmis dans le prompt
	int				i;			//place dans la string
	char			quote;		//quote = \0 si simple = ' si double = "
	struct s_token	*current;	//token en cours
	struct s_token	*head;		//tete de la liste
}					t_state;

t_token	*new_node(char *value, t_type type);
void	add_node(t_token *current, t_state *state);
t_type	get_type(t_state *state);
int	is_operator(char c);
t_token	*to_token(char *line);
int	print_tokens(t_token *token);
void	handle_quote(t_state *state);
void	handle_operator(t_state *state);
void	handle_word(t_state *state);

#endif