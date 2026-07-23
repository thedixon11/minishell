#ifndef MINISHELL_BUILTIN_H
# define MINISHELL_BUILTIN_H

//ft_export
int	create_new_var_env(t_data *data, t_env *env, char *name, char *content);
int	replace_content_value(t_data *data, t_env *current, char *content);
t_env	*does_var_env_exist(t_data *data, t_env *env, char *name);
void	ft_export(t_data *data, t_env *env, char **cmd_args);

//ft_export_utils
char	*get_content_var_env(char *name_n_value);
char	*get_name_var_env(char *name_n_value);
int how_much_args(char **cmd_args);
t_bool	check_var_env_name(char	*name);

//ft_export_print
void	swap_values(char ***env, int i, int j);
void	print_environment(char **env);
void	export_no_args(t_data *data, t_env *env);

#endif
