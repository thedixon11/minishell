#ifndef MINISHELL_XPANSION_H
# define MINISHELL_XPANSION_H

typedef enum e_quote
{
  Q_NONE,
  Q_SINGLE,
  Q_DOUBLE
} t_quote

typedef enum e_bool
{
  B_FALSE,
  B_TRUE
} t_bool

//dollar manager function
char  *dollar_manager(t_data *data, char *str, int *i, t_quote q_mode);

//environment variable manager function
char  *env_var_manager(t_data *data, char *str, int *start);

//quote_manager
char  *quote_manager(t_data *data, char *content, int *i_content, char quote);

//xpansion_utils
char  *second_block_not_dollar_or_quote(char *str, int *i, t_quote q_mode);

#endif
