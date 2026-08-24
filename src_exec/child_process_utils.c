#include "../minishell_general.h"

void	exec_script(char *sh_cmd, char **env)
{
	char	*sh_arg[3];

	sh_arg[0] = "/bin/sh";
	sh_arg[1] = sh_cmd;
	sh_arg[2] = NULL;
	execve("/bin/sh", sh_arg, env);
}
