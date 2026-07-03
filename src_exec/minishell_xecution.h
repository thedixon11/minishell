
// TODO: pas du tout bien structurer, faut encore BEAUCOUP travailler dessus !

#ifndef MINISHELL_XECUTION_H
# define MINISHELL_XECUTION_H

// execution functions
int	execution(t_data *data);
int	execute_cmds(t_data *data);
void	parent_process(t_data *data, int current_cmd_nb);
void	child_process(t_data *data, int current_cmd_nb);
void  dup2_rest(t_data *data, int current_cmd_nb);
void  first_dup2_pipes(t_data *data, int current_cmd_nb);

// heredoc functions
int	heredoc_exec(t_data *data);
int	create_heredoc_fd(t_data *data, t_line *heredoc);
int	write_on_fd(t_data *data, t_line *heredoc, t_bool xpand_or_not);
char	*expand_line_hdoc(t_data *data, char *line, t_bool xpand_or_not);
char	*go_until_dollar_hdoc(t_data *data, char *line, int *start);

// heredoc utils
char	*delimiter_manager_hdoc(t_data *data, char *old_del);
char	*go_until_quote_hdoc(t_data *data, char *old_del, int *i);
char	*extract_quote_hdoc(t_data *data, char *old_del, int *i, char quote);

// check in and out redirections
void	check_and_prepare_fds(t_data *data, int current_cmd_nb);
t_bool	check_in_out_one_file(t_line *line_cmd, int current_cmd_nb);
void	open_fd_in_line_cmd(t_data *data, int current_cmd_nb);

// environment convertert from linked list to env_converter_ll_to_array
char	**env_converter_ll_to_array(t_data *data, t_env *env);
char	*rebuild_value(t_data *data, t_env *current);

// preparation of material before execve

t_cmd	*execve_preparation(t_data *data, char **cmd_content);
char	*create_prog_fullname(t_data *data, t_cmd *cmd_data, char *prog_name);
char	**create_path_array(t_data *data, char *path_to_split);
int	is_prog_existing_and_executable(t_data *data, char *path_to_check);

// execution utils

void	free_and_close_life(t_data *data);
void	close_all_fd(t_line *line_cmd);
void	free_line_cmd(t_line *line_cmd);
void	free_env(t_env *env);
void	free_cmd_data(t_cmd *cmd_data);
int		ft_error(t_data *data, char *err_message, int code, t_scope scope);
void	ft_error_child(t_data *data, t_bool do_i_perror, char *message,
			int code);
void	ft_free(void **ptr);
void  wait_all_children(t_data *data);
void  close_fd(int *fd);

// ft_error
void	ft_error_child(t_data *data, t_bool do_i_perror, char *message, int code);
char	*ft_error_parent(t_bool do_i_perror, char *message, int code);
int	ft_error_parent_int(t_bool do_i_perror, char *message, int code);

#endif
