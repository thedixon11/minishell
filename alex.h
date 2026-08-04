
#ifndef ALEX_H
# define ALEX_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_type
{
	T_INPUT,
	T_OUTPUT_TRUNC,
	T_OUTPUT_APPEND,
	T_HEREDOC,
	T_PIPE_IN,
	T_PIPE_OUT,
	T_COMMAND,
	T_PIPE
}	t_type;

typedef struct s_line
{
	t_type			type;
	char			*content;
	char			**content_xpand;
	int				fd;
	int				cmd_nb;
	struct s_line	*prev;
	struct s_line	*next;
}					t_line;

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
int		is_operator(char c);
t_token	*to_token(char *line);
// int		print_tokens(t_token *token);
void	handle_quote(t_state *state);
void	handle_operator(t_state *state);
void	handle_word(t_state *state);
t_line	*to_parse(t_token *head);
void	handle_command(t_token *token, t_line **head, int cmd_nb);
void	handle_pipe(int *cmd_nb, t_line **head);
int		handle_redir(t_token *token, int cmd_nb, t_line **head);
void	add_line(t_line *current, t_line **head);
t_line	*new_line(t_type type, int cmd_nb, char *content);
int		print_lines(t_line *lines);
t_line *fusion_commands(t_line *head);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
size_t	ft_strlcat(char *dst, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
void	*ft_memcpy(void *dest, const void *src, size_t n);


#endif