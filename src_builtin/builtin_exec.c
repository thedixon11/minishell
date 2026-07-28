#include "../minishell_general.h"
#include "minishell_builtin.h"

void	execute_builtin(t_data *data)
{
	t_line	*current;

	current = move_current_to_cmd(data);
	if (ft_strncmp(current->content_xpand[0], "echo", 5) == 0)
		ft_echo(data, current->content_xpand);
	else if (ft_strncmp(current->content_xpand[0], "cd", 3) == 0)
		ft_cd(data, current->content_xpand);
	else if (ft_strncmp(current->content_xpand[0], "pwd", 4) == 0)
		ft_pwd();
	else if (ft_strncmp(current->content_xpand[0], "export", 7) == 0)
		ft_export(data, current->content_xpand);
	else if (ft_strncmp(current->content_xpand[0], "unset", 6) == 0)
		ft_unset(data, current->content_xpand);
	else if (ft_strncmp(current->content_xpand[0], "env", 4) == 0)
		ft_env(data, current->content_xpand);
	else if (ft_strncmp(current->content_xpand[0], "exit", 5) == 0)
		ft_exit(data, current->content_xpand);
}

t_bool	is_there_pipes(t_data *data)
{
	t_line	*current;

	current = data->line_cmd;
	while (current != NULL)
	{
		if (current->type == T_PIPE_IN || current->type == T_PIPE_OUT)
			return (B_TRUE);
		current = current->next;
	}
	return (B_FALSE);
}

t_bool	is_echo_pwd_env(t_data *data)
{
	t_line	*current;

	current = move_current_to_cmd(data);
	if (ft_strncmp(current->content_xpand[0], "echo", 5) == 0)
		return (B_FALSE);
	else if (ft_strncmp(current->content_xpand[0], "pwd", 4) == 0)
		return (B_FALSE);
	else if (ft_strncmp(current->content_xpand[0], "env", 4) == 0)
		return (B_FALSE);
	else
	 return (B_TRUE);
}

t_bool	is_it_builtin(t_data *data)
{
	t_line	*current;

	current = move_current_to_cmd(data);
	if (ft_strncmp(current->content_xpand[0], "echo", 5) == 0)
		return (B_TRUE);
	else if (ft_strncmp(current->content_xpand[0], "cd", 3) == 0)
		return (B_TRUE);
	else if (ft_strncmp(current->content_xpand[0], "pwd", 4) == 0)
		return (B_TRUE);
	else if (ft_strncmp(current->content_xpand[0], "export", 7) == 0)
		return (B_TRUE);
	else if (ft_strncmp(current->content_xpand[0], "unset", 6) == 0)
		return (B_TRUE);
	else if (ft_strncmp(current->content_xpand[0], "env", 4) == 0)
		return (B_TRUE);
	else if (ft_strncmp(current->content_xpand[0], "exit", 5) == 0)
		return (B_TRUE);
	else
		return (B_FALSE);
}

int	execute_builtin_parent(t_data *data)
{
	if (manage_redirections(data) == 1)
		return (1);
	execute_builtin(data);
	return (0);
}
