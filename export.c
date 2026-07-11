
int	ft_export(t_data *data, t_line *cmd)
{
	int	y;

	y = 0;
	
	if (data->while
		
	while (cmd->content_xpand[y] != NULL)
		y++;
	if (y == 1)
		print_env_sorted(data);
	else
		execute_export(data);
}
