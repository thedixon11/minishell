#ifndef MINISHELL_XPANSION_H
# define MINISHELL_XPANSION_H

// value manager functions
int		val_manager(t_data *data);
char	*manage_before_split(t_data *data, char *content);
int		content_splitted_manager(t_data *data, char **content_to_xpand);
char	*expand_off_quote(t_data *data, char *content);
char	*expand_in_quote(t_data *data, char *row);

// value manager utils
char	*go_until_quote(t_data *data, char *content, int *start);
char	*go_until_dollar(t_data *data, char *content, int *start);
void	jump_quoted_content(char *content, int *end);

// dollar manager functions
char	*dollar_manager(t_data *data, char *str, int *i, t_quote q_mode);

//dollar_manager_utils
char	*dollar_not_alphanum_and_err(t_data *data, char *str, int *i);
char	*dollar_is_error_code(t_data *data, int *i);
char	*zero_after_dollar(t_data *data, int *i);
char	*quote_after_dollar(t_data *data, int *i);
char	*digit_after_dollar(t_data *data, int *i);

// environment variable manager functions
char	*env_var_manager(t_data *data, char *str, int *start);
char	*extract_env_var(t_data *data, char *str, int *i);
char	*env_var_checker(t_data *data, t_env *env, char *var_env);

// quote_manager functions
char	*quote_manager(t_data *data, char *value, int *i_value, char quote);
char	*extract_quote(t_data *data, char *value, int *i_value, char quote);
char	*quote_expansion(t_data *data, char *inside_quote);
char	*second_block_not_dollar(t_data *data, char *str, int *i);

#endif
