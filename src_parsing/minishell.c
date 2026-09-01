/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:23:43 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:23:44 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"
#include <readline/readline.h>
#include <string.h>

int	g_signal;

t_data	*data_init(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
	{
		error_int(data, I_CALLOC, LIBFT_ERR, 1);
		exit(1);
	}
	data->code = 0;
	data->max_cmd_nb = 0;
	data->line_cmd = NULL;
	data->do_i_exit = B_TRUE;
	data->cwd = getcwd(NULL, 0);
	if (!data->cwd)
		error_int(data, I_GETCWD, strerror(errno), 1);
	data->old_cwd = ft_strdup(data->cwd);
	if (!data->old_cwd)
		error_int(data, I_STRDUP, LIBFT_ERR, 1);
	return (data);
}

void	line_reader_and_exec(t_data *data)
{
	char	*line;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
			handle_ctrl_d(data);
		add_history(line);
		if (line[0] != 0)
		{
			if (to_token(line, data) == 1)
				continue ;
			if (control_token_line(data) == 1)
				continue ;
			if (to_parse(data) == 1)
				continue ;
			handle_ctrl_c(data);
			init_signal_prompt();
			free_token_ll(&data->token_head);
			execution_start(data);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	*data;
	int		code;

	(void)argv;
	if (argc > 1)
		return (error_no_data(I_MINISHELL, MINI_ARGS, 1));
	init_signal_prompt();
	code = 0;
	data = data_init();
	initialize_env(data, envp);
	line_reader_and_exec(data);
	data->do_i_exit = B_TRUE;
	code = data->code;
	free_and_close_life(data);
	rl_clear_history();
	return (code);
}
