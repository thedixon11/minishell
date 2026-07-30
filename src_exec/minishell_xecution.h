#ifndef MINISHELL_XECUTION_H
# define MINISHELL_XECUTION_H

//execution_start
int	store_stdin_stdout(t_data *data);
int	execution_start(t_data *data);

//classic_execution
void	parent_process(t_data *data);
int	time_to_fork_and_exec(t_data *data);
int	time_to_pipe(t_data *data);
void	classic_execution(t_data *data);

//child_process
void	check_cmd_is_not_empty(t_data *data, t_line *current);
void	child_process(t_data *data);
void	child_no_builtin(t_data *data);

//manage_redirections
int	patch_others_redir(t_data *data);
int	first_patch_pipes_redir(t_data *data);
int	open_fd_in_line_cmd(t_data *data);
int	check_ambiguous_redir(t_data *data);
int	manage_redirections(t_data *data);

//execute_cmds
void	close_used_fd(t_data *data);
t_bool	do_i_parent(t_data *data);
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

//some_utils
t_bool	exec_builtin_or_not(t_data *data);
t_line	*move_current_to_start(t_data *data);
t_line	*move_current_to_cmd(t_data *data);
void	free_and_close_life(t_data *data);
void	dup2_process(t_data *data, int *fd1, int fd2);
void	free_cmd_data(t_data *data);

#endif
