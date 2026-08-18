#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

// minishell.c
int	main(int argc, char **argv, char **envp);
int	print_env(t_env	*env);
int	print_tokens(t_token *token);
int	print_lines(t_line *lines);
void	free_token_ll(t_token *token);

// create_env.c
t_env	*create_env(char **envp);
void	add_node_env(t_env	*current, t_env **head);
t_env	*new_node_env(char *line);
char	*ft_strndup(const char *s, size_t n);

// node_utils.c
t_token	*new_node(t_data *data, char *value, t_type type);
void	add_node(t_token *current, t_state *state);

// parse_utils.c
t_line	*new_line(t_type type, int cmd_nb, char *content);
void	add_line(t_line *current, t_line **head);

// to_parse.c
t_line *fusion_commands(t_line *head);
t_line	*to_parse(int *max_cmd_nb, t_token *head);
void	handle_command(t_token *token, t_line **head, int cmd_nb);
void	handle_pipe(int *cmd_nb, t_line **head);
int	handle_redir(t_token *token, int cmd_nb, t_line **head);

// to_token.c
t_token	*to_token(char *line, t_data *data);
int		handle_quote(t_state *state, t_data *data);
int		handle_operator(t_state *state, t_data *data);
int		handle_word(t_state *state, t_data *data);

// to_token_utils.c
int	is_operator(char c);
t_type	get_type(t_state *state);

// is_there_env
int	initialize_env(t_data *data, char **envp);
t_bool	check_if_value_exist(t_data *data, char *value);
int	create_new_env(t_data *data);

//is_there_env_utils
int	create_pwd_value(t_data *data);
int	create_shlvl_value(t_data *data);
int	update_pwd_value(t_data *data);
int	update_shlvl_value(t_data *data);

#endif
