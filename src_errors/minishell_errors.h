#ifndef MINISHELL_ERRORS_H
# define MINISHELL_ERRORS_H

int	error_int(t_data *data, char *item, char *message, int code);
char	*error_char(t_data *data, char *item, char *message, int code);

//ft_error
void	ft_error_child(t_data *data, char *message, int code);
void	ft_error_child_cmd_not_found(t_data *data, char *message, int code);
int	ft_error_parent_amb_redir(t_data *data, char *message, int code);
char	*ft_error_parent_char(t_data *data, char *message, int code);
int	ft_error_parent_int(t_data *data, char *message, int code);

//ft_free
void	free_line_cmd(t_line *line_cmd);
void	free_env(t_env *env);
void	free_cmd_args(t_data *data);

//close_fd_utils
void	close_line_cmd_fds(t_data *data);
void	close_line_cmd_fds_full(t_data *data);
void	close_data_fds(t_data *data);

#endif
