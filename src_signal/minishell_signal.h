#ifndef MINISHELL_SIGNAL_H
# define MINISHELL_SIGNAL_H

// signal.c
void	signal_handler(int signo);
void	signal_handler_heredoc(int signo);
void	handle_ctrl_c(t_data *data);
void	handle_ctrl_d(t_data *data);
void	signal_handler_exec(int signo);

// init_signal.c
void	init_signal_prompt(void);
void	init_signal_heredoc(void);
void	init_signal_parent(void);
void	init_signal_child(void);

#endif
