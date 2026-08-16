#ifndef MINISHELL_BUILTIN_H
# define MINISHELL_BUILTIN_H

// builtin_exec
int		execute_builtin_parent(t_data *data);
t_bool	is_it_builtin(t_data *data);
t_bool	is_echo_pwd_env(t_data *data);
t_bool	is_there_pipes(t_data *data);
int		execute_builtin(t_data *data);

// ft_export
int		ft_export(t_data *data, char **cmd_args);
int		repl_create_var(t_data *data, char *name, char *content);
t_env	*does_var_env_exist(t_data *data, char *name);
int		replace_content_value(t_data *data, t_env *current, char *content);
int		create_new_var_env(t_data *data, char *name, char *content);

// ft_export_utils
char	*get_content_var_env(t_data *data, char *name_n_value);
char	*get_name_var_env(t_data *data, char *name_n_value);
int		how_much_args(char **cmd_args);
t_bool	check_var_env_name(t_data *data, char **name, char *identifier, int *y);
void	print_var_error(char *identifier);

//ft_export_utils two

int		add_quotes_content(t_data *data, char ***c_env);
char	*add_quotes_content_util(t_data *data, char **name, char **content);

// ft_export_print
void	swap_values(char ***env, int *i, int j);
void	print_environment(char **env);
int		export_no_args(t_data *data);

// ft_echo
int		ft_echo(t_data *data, char **args_cmd);
t_bool	skip_option_n(t_data *data, char **args_cmd, int *y);
void	echo_no_args(t_data *data);

// ft_cd
int		update_env_wd(t_data *data);
int		update_data_wd(t_data *data, char *pathname);
int		change_cwd_to_home(t_data *data);
int		check_nb_args_cd(t_data *data, char **cmd_args);
int		ft_cd(t_data *data, char **cmd_args);

// ft_cd_utils
int		update_data_wd_home(t_data *data);
char	*search_home_var(t_data *data);
int		ft_cd_error(t_data *data, char *path, char *message, int code);

// ft_pwd
int		ft_pwd(t_data *data);

// ft_unset
int		ft_unset(t_data *data, char **cmd_args);
int		remove_the_env_var(t_data *data, char *env_var_to_rm);

// ft_env
int		ft_env(t_data *data, char **cmd_args);

// ft_exit
int		ft_exit(t_data *data, char **cmd_args);

#endif
