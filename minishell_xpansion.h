#ifndef MINISHELL_XPANSION_H
# define MINISHELL_XPANSION_H

typedef enum e_quote
{
  Q_NONE,
  Q_SINGLE,
  Q_DOUBLE,
  Q_HEREDOC,
} t_quote;

typedef enum e_bool
{
  B_FALSE,
  B_TRUE
} t_bool;

//value manager functions
char  **val_manager(char *content);
char  *expand_off_quote(t_data *data, char *content);
char  *expand_in_quote(t_data *data, char *row);
char  *go_until_quote(char *content, int *start);
char  *go_until_dollar(char *content, int *start);

//dollar manager functions
char  *dollar_manager(t_data *data, char *str, int *i, t_quote q_mode);

//environment variable manager functions
char  *env_var_manager(t_data *data, char *str, int *start);
char  *extract_env_var(char *str, int *i);
char  *env_var_checker(t_env *env, char *var_env);

//quote_manager functions
char  *quote_manager(t_data *data, char *content, int *i_content, char quote);
char  *extract_quote(char *value, int *i_value, char quote);
char  *quote_expansion(t_data *data, char *inside_quote);
char  *second_block_not_dollar_or_quote(char *str, int *i, t_quote q_mode);
t_bool is_it_dollar_or_quote(char c, t_quote q_mode);

#endif
