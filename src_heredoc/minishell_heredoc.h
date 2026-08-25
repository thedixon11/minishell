/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_heredoc.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:13:31 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:13:32 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_HEREDOC_H
# define MINISHELL_HEREDOC_H

// heredoc_exec
int		heredoc_exec(t_data *data);
int		delimiter_manager_n_write_hdoc(t_data *data, t_line *current);
int		create_heredoc_fd(t_data *data, t_line *heredoc);

// heredoc_exec_utils
char	*remove_n_xtract_quotes_hdoc(t_data *data, char *old_del);
char	*go_until_dollar_hdoc(t_data *data, char *line, int *start);
char	*go_until_quote_hdoc(t_data *data, char *old_del, int *start);
char	*extract_quote_hdoc(t_data *data, char *old_del, int *start,
			char quote);
char	*fusion_first_second_block(t_data *data, char *first, char *second);

// heredoc_child_parent
void	heredoc_parent(t_data *data, int *error);
void	heredoc_child(t_data *data, t_line *current);

// write_on_fd
int		write_on_fd(t_data *data, t_line *heredoc, t_bool xpand);
char	*create_line(t_data *data, t_line *hdoc, t_bool xpand, int *error);
char	*expand_line_hdoc(t_data *data, char *line);

// delimiter_manager
char	*expand_off_quote_hdoc(t_data *data, char *content);
char	*dollar_manager_hdoc(t_data *data, char *str, int *i);
char	*zero_after_dollar_hdoc(t_data *data, int *i);
char	*quote_after_dollar_hdoc(t_data *data, int *i);
char	*esle_after_dollar_hdoc(t_data *data, char *str, int *i);

#endif
