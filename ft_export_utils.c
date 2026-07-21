char	*get_content_var_env(char *name_n_value)
{
	int start;
	int	end;
	char	*content;

	start = 0;
	len = 0;
	while (name_n_value [start] != 0 && name_n_value[start] != '='))
		start++;
	if (name_n_value[start] == 0)
		return (NULL);
	start++;
	end = start;
	while (name_n_value[end] != 0)
		end++;
	content = ft_substr(name_n_value, start, end - start);
	data->errno = errno;
	if (!name)
		ft_error_parent_char();
	return (content);
}


char	*get_name_var_env(char *name_n_value)
{
	int	len;
	char	*name;

	len = 0;
	while (name_n_value[i] != 0 && name_n_value[i] != '=')
		len++;
	name = ft_substr(name_n_value, 0, len);
	data->errno = errno;
	if (!name)
		ft_error_parent_char();
	return (name);
}
