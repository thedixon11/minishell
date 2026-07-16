void	manage_value_export(t_data *data, t_line *cmd, char *value)
{
	int		y;
	t_env	

	y = 1;
}


void	add_to_env(t_data *data)
{
	if (check_if_already_exists(data) == B_TRUE)
}

int	ft_export(t_data *data, t_line *cmd)
{
	int	y;

	y = 1;
	

	while (cmd->content_xpand[y] != NULL)
		manage_value_export(data, cmd->content_xpand[y]);
	if (y == 1)
		print_env_sorted(data);
}
