
int	check_nb_args_cd(char **cmd_args)
{
	int	y;
	
	y = 0;
	while (cmd_args[y] != NULL)
		y++;
	if (y > 2)
		return (ft_error_parent_int(data, "too much args bro in cd", 1));
	return (0);
}

int	ft_cd(t_data *data, char **cmd_args)
{
	if (check_nb_args_cd(cmd_args) == 1)
		return (1);
}
