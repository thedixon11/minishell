#ifndef MINISHELL_XPANSION_H
# define MINISHELL_XPANSION_H

// value manager functions
int	val_manager(t_data *data);
char	*expand_off_quote(t_data *data, char *content);
char	*expand_in_quote(t_data *data, char *row);
char	*go_until_quote(t_data *data, char *content, int *start);
char	*go_until_dollar(t_data *data, char *content, int *start);

// dollar manager functions
char	*dollar_manager(t_data *data, char *str, int *i, t_quote q_mode);

// environment variable manager functions
char	*env_var_manager(t_data *data, char *str, int *start);
char	*extract_env_var(char *str, int *i);
char	*env_var_checker(t_env *env, char *var_env);

// quote_manager functions
char	*quote_manager(t_data *data, char *value, int *i_value, char quote);
char	*extract_quote(char *value, int *i_value, char quote);
char	*quote_expansion(t_data *data, char *inside_quote);
char	*second_block_not_dollar(char *str, int *i);

#endif
