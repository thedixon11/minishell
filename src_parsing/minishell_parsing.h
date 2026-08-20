#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

// minishell.c
int		main(int argc, char **argv, char **envp);
int		print_env(t_env *env);
int		print_tokens(t_token *token);
int		print_lines(t_line *lines);

// signal.c
int		end_heredoc(char *line);
void    setup_signals(void);
void    handle_sigint(int sig);
void    handle_sigint_heredoc(int sig);
void	handle_sigint_exec(int sig);

// create_env.c
t_env	*create_env(char **envp);
void	add_node_env(t_env *current, t_env **head);
t_env	*new_node_env(char *line);
char	*ft_strndup(const char *s, size_t n);

// node_utils.c
t_token	*new_token_node(t_data *data, char *value, t_type type);
void	add_token(t_data *data, t_token *current);

// parse_utils.c
t_line	*new_line(t_data *data, t_type type, int cmd_nb, char *content);
void	add_line(t_data *data, t_line *current);

// to_parse.c
int		handle_token_line(t_data *data);
int		to_parse(t_data *data);
int		handle_command(t_data *data, t_token *current, int cmd_nb);
int		handle_pipe(t_data *data, int *cmd_nb);
int		handle_redir(t_data *data, t_token *token, int cmd_nb);

// to_parse_fusion_cmd.c
int		join_all_cmd_content(t_data *data, t_line *current, t_line *to_fusion);
int		move_skip(t_data *data, t_line *current);
int		fusion_commands(t_data *data);

// to_token.c
void	state_init(t_state *state, char *line);
int		to_token(char *line, t_data *data);
int		handle_quote(t_state *state, t_data *data);
int		handle_operator(t_state *state, t_data *data);
int		handle_word(t_state *state, t_data *data);

// to_token_utils.c
int		is_operator(char c);
t_type	get_type(t_state *state);

// to_token_control
int		control_token_line(t_data *data);
t_bool	operator_or_not(t_token *current);
int		control_the_operator(t_data *data, t_token *current);
int		control_classic_redir(t_data *data, t_token *current);
int		control_pipe_redir(t_data *data, t_token *current);

// is_there_env
int		initialize_env(t_data *data, char **envp);
t_bool	check_if_value_exist(t_data *data, char *value);
int		create_new_env(t_data *data);

// is_there_env_utils
int		create_pwd_value(t_data *data);
int		create_shlvl_value(t_data *data);
int		update_pwd_value(t_data *data);
int		update_shlvl_value(t_data *data);

// signals
void	handle_sigint(int sig);
void	handle_sigint_heredoc(int sig);

#endif
