#ifndef MINISHELL_ERRORS_H
# define MINISHELL_ERRORS_H

//ft_error
char	*error_char(t_data *data, char *item, char *message, int code);
int		error_int(t_data *data, char *item, char *message, int code);
int		error_no_data(char *item, char *message, int code);
t_token	*error_token(t_state *state, char *message, int code, t_bool do_i_exit);

//ft_free
void	free_line_cmd(t_line **line_cmd);
void	free_env(t_env **env);
void	free_cmd_args(t_data *data);
void	free_token_ll(t_token *token);
void	free_state_data(t_state *state);

//close_fd_utils
void	close_line_cmd_fds(t_data *data);
void	close_line_cmd_fds_full(t_data *data);
void	close_data_fds(t_data *data);

#endif
