#ifndef MINISHELL_XECUTION_H
# define MINISHELL_XECUTION_H

//execution_start
int	store_stdin_stdout(t_data *data);
int	execution_start(t_data *data);

//classic_execution
void	parent_process(t_data *data);
int	time_to_fork_and_exec(t_data *data);
int	time_to_pipe(t_data *data);
int	classic_execution(t_data *data);

//child_process
void	check_cmd_is_not_empty(t_data *data, t_line *current);
void	child_process(t_data *data);
void	child_no_builtin(t_data *data);

//ft_error
int	ft_error_parent_int(t_data *data, char *message, int code);
char	*ft_error_parent_char(t_data *data, char *message, int code);
void	ft_error_child_cmd_not_found(t_data *data, char *message, int code);
int	ft_error_parent_amb_redir(t_data *data, char *message, int code);
void	ft_error_child(t_data *data, char *message, int code);

//manage_redirections
int	patch_others_redir(t_data *data);
int	first_patch_pipes_redir(t_data *data);
int	open_fd_in_line_cmd(t_data *data);
int	check_ambiguous_redir(t_data *data);
int	manage_redirections(t_data *data);

//execute_cmds
void	save_pipe_rd_to_old_read_fd(t_data *data);
void	wait_all_children(t_data *data);
int	reset_redir_patch(t_data *data);
int	execute_cmds(t_data *data);

//env_converter_ll_to_array
char	*rebuild_value(t_data *data, t_env *current);
char	**env_converter_ll_to_array(t_data *data, t_env *env);

//execve_preparation
int	is_prog_existing_and_executable(t_data *data, char *path_to_check);
char	**find_path_tab(t_data *data);

//execve_preparation_utils
char	**create_path_tab(t_data *data, char *path_to_split);
char	*join_path_prog(t_data *data, char *path, char *prog_name);
char	*check_prog_in_path(t_data *data, char **path_tab, char *prog_name);
char	*prog_name_prep(t_data *data, char **path_tab, char **cmd_content);

//heredoc_exec
int	create_heredoc_fd(t_data *data, t_line *heredoc);
int	no_quotes_in_delimiter(t_data *data, t_line *current);
int	heredoc_exec(t_data *data);

//heredoc_exec_utils
char	*fusion_first_second_block(t_data *data, char *first, char *second);
char	*extract_quote_hdoc(t_data *data, char *old_del, int *start, char quote);
char	*go_until_quote_hdoc(t_data *data, char *old_del, int *start);
char	*go_until_dollar_hdoc(t_data *data, char *line, int *start);
char	*delimiter_manager_hdoc(t_data *data, char *old_del);

//write_on_fd
char	*expand_line_hdoc(t_data *data, char *line);
char	*create_line(t_data *data, t_line *heredoc, t_bool xpand_or_not);
int	write_on_fd(t_data *data, t_line *heredoc, t_bool xpand_or_not);

//some_utils
t_bool	exec_builtin_or_not(t_data *data);
t_line	*move_current_to_start(t_data *data);
t_line	*move_current_to_cmd(t_data *data);
void	free_and_close_life(t_data *data);
void	dup2_process(t_data *data, int *fd1, int fd2);
void	free_cmd_data(t_data *data);

//close_fd_utils
void	close_data_fds(t_data *data);
void	close_line_cmd_fds(t_data *data);

//heredoc_exec_utils
void	free_env(t_env *env);
void	free_line_cmd(t_line *line_cmd);

#endif
