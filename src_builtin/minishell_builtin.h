#ifndef MINISHELL_BUILTIN_H
# define MINISHELL_BUILTIN_H

//builtin_exec
t_bool	exec_builtin_or_not(t_data *data);
int	builtin_execution(t_data *data, t_bool do_i_parent);

//ft_export
int		create_new_var_env(t_data *data, char *name, char *content);
int		replace_content_value(t_data *data, t_env *current, char *content);
t_env	*does_var_env_exist(t_data *data, char *name);
int	ft_export(t_data *data, char **cmd_args);
void	print_var_error(char *identifier);
void	repl_create_var(t_data *data, char *name,
			char *content, t_env *current);

//ft_export_utils
char	*get_content_var_env(t_data *data, char *name_n_value);
char	*get_name_var_env(t_data *data, char *name_n_value);
int		how_much_args(char **cmd_args);
t_bool	check_var_env_name(char	*name);

//ft_export_print
void	swap_values(char ***env, int *i, int j);
void	print_environment(char **env);
void	export_no_args(t_data *data);
int		add_quotes_content(t_data *data, char ***c_env);

//ft_echo
int	ft_echo(t_data *data, char **args_cmd);
t_bool	skip_option_n(char **args_cmd, int *y);

//ft_cd
int	update_env_wd(t_data *data);
int	update_data_wd(t_data *data, char *pathname);
int	change_cwd_to_home(t_data *data);
int	check_nb_args_cd(t_data *data, char **cmd_args);
int	ft_cd(t_data *data, char **cmd_args);
#endif
