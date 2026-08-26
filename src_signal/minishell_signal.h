/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_signal.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:15:14 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:15:15 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_SIGNAL_H
# define MINISHELL_SIGNAL_H

// signal.c
void	signal_handler(int signo);
void	signal_handler_heredoc(int signo);
void	handle_ctrl_c(t_data *data);
void	handle_ctrl_d(t_data *data);
void	report_signaled_child(t_data *data, int status);

// init_signal.c
void	init_signal_prompt(void);
void	init_signal_heredoc(void);
int		heredoc_event_hook(void);
void	init_signal_parent(void);
void	init_signal_child(void);

#endif
