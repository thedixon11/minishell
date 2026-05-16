#ifndef MINISHELL_XPANSION_H
# define MINISHELL_XPANSION_H

//dollar manager function
char  *dollar_manager(t_data *data, char *str, int *i, t_quote q_mode);

//environment variable manager function
char  *env_var_manager(t_data *data, char *str, int *i);
#endif
