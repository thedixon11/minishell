#ifndef MINISHELL_HEREDOC_H
# define MINISHELL_HEREDOC_H

//heredoc_exec
int	heredoc_exec(t_data *data);
int	no_quotes_in_delimiter(t_data *data, t_line *current);
int	create_heredoc_fd(t_data *data, t_line *heredoc);

//heredoc_exec_utils
char	*delimiter_manager_hdoc(t_data *data, char *old_del);
char	*go_until_dollar_hdoc(t_data *data, char *line, int *start);
char	*go_until_quote_hdoc(t_data *data, char *old_del, int *start);
char	*extract_quote_hdoc(t_data *data, char *old_del, int *start, char quote);
char	*fusion_first_second_block(t_data *data, char *first, char *second);

//write_on_fd
int	write_on_fd(t_data *data, t_line *heredoc, t_bool xpand_or_not);
char	*create_line(t_data *data, t_line *heredoc, t_bool xpand_or_not);
char	*expand_line_hdoc(t_data *data, char *line);

#endif
