#include "minishell_xecution.h"

int	is_binary_existing_and_executable(char *path_to_check)
{
  //NOTE: ici on check si le binaire existe et s'il est executable
	if (access(path_to_check, F_OK) != 0)
		return (-1);
	if (access(path_to_check, X_OK) != 0)
		return (-1);
	return (0);
}

char	**create_path_array(t_env *env)
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

char  *create_prog_fullname(char **path_array, char *prog_name)
{
  //NOTE: ici la fonction qui va verifier le nom du binaire dans tout les 
  //directory du PATH, on va chaque fois strjoin le nom du binaire avec le 
  //path tester.

	size_t	y;
	char	*temp;
  char  *prog_fullname;

	y = 0;
	temp = ft_strjoin("/", prog_name);
	if (temp == NULL)
		errors_exit(data, MALLOC_ERR, 0, 0);
	while (path_array[y] != NULL)
	{
		prog_fullname = ft_strjoin(path_array[y], temp);
		if (prog_fullname == NULL)
			errors_exit(data, MALLOC_ERR, 0, 0);
		if (is_binary_existing_and_executable(prog_fullname) == 0)
		{
			free(temp);
			return (prog_fullname);
		}
		free(prog_fullname);
		y++;
	}
	free(temp);
	return (NULL);
}

t_cmd *execve_preparation(t_data *data, char **cmd_content)
{
  //NOTE: ici on va preparer le necessaire pour l'execve

  t_cmd *cmd_data;
  t_env  *current;

  //NOTE: cmd_data doit contenir :
  //le nom du programme complet
  //le tableau des args
  //le tableau avec les differents paths
  //le tableau d'env converti

  current = data->env;
  cmd_data = ft_calloc(1, sizeof(t_cmd));
  if (!cmd_data)
    return (NULL);

  //NOTE: le tableau des args sera deja fait par Alex et est 
  //stocker dans la node de la cmd
  cmd_data->args_array = cmd_content;

  //NOTE: l'env est converti au debut du programme par ALEX de array a linked list
  //et est stocker dans data 
  //mais pour execve, il faut reconvertir l'env de linked list a array
  cmd_data->env = env_converter_ll_to_array(data->env);

  //NOTE: le path est encore dans la liste chainee de l'environnement sur une string
  //il faut la convertir en array et sans le "PATH=" au debut
  while (current != NULL);
  {
    if (ft_strncmp(current->name, "PATH", 5) == 0)
      cmd_data->path_array = create_path_array(current->content);
    current = current->next;
  }

  //NOTE: si on trouve pas de slash, ce n'est pas un relative or absolute
  //path. Il faut donc chercher dans le path avec la fonction create_prog_fullname
  if (ft_strchr(cmd_data->args_array[0], '/') == 0)
    cmd_data->prog_fullname = create_prog_fullname(cmd_data->path_array, cmd_content[0]);

  //NOTE: si il y a un slash, c'est soit un relative or absolute, donc faut verifier qu'il existe
  else
    cmd_data->prog_fullname = ft_strdup(cmd_data->args_array[0]);
  if (is_prog_existing_and_executable(cmd_data->prog_fullname) != 0)
    return (NULL);
  return (cmd_data);
}
