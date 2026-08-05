#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

t_data	*data_creation(void);
t_token	*new_node(char *value, t_type type);
void	add_node(t_token *current, t_state *state);
t_type	get_type(t_state *state);
int		is_operator(char c);
t_token	*to_token(char *line);
// int		print_tokens(t_token *token);
void	handle_quote(t_state *state);
void	handle_operator(t_state *state);
void	handle_word(t_state *state);
t_line	*to_parse(int *max_cmd_nb, t_token *head);
void	handle_command(t_token *token, t_line **head, int cmd_nb);
void	handle_pipe(int *cmd_nb, t_line **head);
int		handle_redir(t_token *token, int cmd_nb, t_line **head);
void	add_line(t_line *current, t_line **head);
t_line	*new_line(t_type type, int cmd_nb, char *content);
int		print_lines(t_line *lines);
t_line	*fusion_commands(t_line *head);
int		print_env(t_env	*env);
char	*ft_strndup(const char *s, size_t n);

#endif
