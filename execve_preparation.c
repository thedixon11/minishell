#include "minishell_xecution.h"

int	is_binary_existing_and_executable(char *path_to_check)
{
  //NOTE: ici on check si le bnaire existe et s'il est executable
	if (access(path_to_check, F_OK) != 0)
		return (-1);
	if (access(path_to_check, X_OK) != 0)
		return (-1);
	return (0);
}

void	create_path_array(t_cmd *cmd_data)
{
  //NOTE: ici la fonction qui va creer le tableau de PATH. 

	char	*path_to_split;
	size_t	y;

	y = 0;
	while (cmd_data->env[y] != NULL)
	{
		if (ft_strncmp(data->env[y], "PATH", 4) == 0)
		{
			path_to_split = ft_strrm(data->env[y], 4);
			if (path_to_split == NULL)
				errors_exit(data, MALLOC_ERR, 0, 0);
			cmd_data->path_array = ft_split(path_to_split, ':');
			if (cmd_data->path_array == NULL)
				errors_exit(data, MALLOC_ERR, 0, 0);
			free(path_to_split);
			return ;
		}
		y++;
	}
	cmd_data->path_array = NULL;
	return (data);
}

void  create_prog_fullname(t_cmd *cmd_data)
{
  //NOTE: ici la fonction qui va verifier le nom du binaire dans tout les 
  //directory du PATH, on va chaque fois strjoin le nom du binaire avec le 
  //path tester.

	size_t	y;
	char	*temp;

	y = 0;
	temp = ft_strjoin("/", cmd_data->args_array[0]);
	if (temp == NULL)
		errors_exit(data, MALLOC_ERR, 0, 0);
	while (cmd_data->path_array[y] != NULL)
	{
		cmd_data->prog_fullname = ft_strjoin(cmd_data->path_array[y], temp);
		if (cmd_data->prog_fullname == NULL)
			errors_exit(data, MALLOC_ERR, 0, 0);
		if (is_binary_existing_and_executable(cmd_data->prog_fullname) == 0)
		{
			free(temp);
			return ;
		}
		free(cmd_data->prog_fullname);
		y++;
	}
	free(temp);
	cmd_data->prog_fullname = NULL;
}

t_cmd *execve_preparation(t_data *data)
{
  //NOTE: ici on va preparer le necessaire pour l'execve

  t_cmd *cmd_data;

  //NOTE: cmd_data doit contenir :
  //le nom du programme complet
  //le tableau des args
  //le tableau avec les differents paths
  //le tableau d'env

  cmd_data = ft_calloc(1, sizeof(t_cmd));
  if (!cmd_data)
    return (NULL);

  //NOTE: le tableau des args sera deja fait par Alex et est 
  //stocker de base dans data
  cmd_data->args_array = data->cmd_array;

  //NOTE: l'env sera fait par Alex et est stocker de base
  //dans data
  cmd_data->env = data->env;

  //NOTE: la fonction pour creer le tableau de path
  create_path_array(cmd_data);

  //NOTE: si on trouve pas de slash, ce n'est pas un relative or absolute
  //path. Il faut donc chercher dans le path avec la fonction create_prog_fullname
  if (ft_strchr(cmd_data->args_array[0], '/') == 0)
    create_prog_fullname(cmd_data);

  //NOTE: si il y a un slash, c'est soit un relative or absolute, donc faut verifier qu'il existe
  else
    cmd_data->prog_fullname = cmd_data->args_array;
  if (is_prog_existing_and_executable(cmd_data->prog_fullname) != 0)
    return (NULL);
  return (cmd_data);
}
