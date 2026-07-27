#include "../minishell_general.h"

int	ft_pwd(void)
{
	char	*cwd_to_print;

	cwd_to_print = getcwd(NULL, 0);
	ft_print("%s\n", cwd_to_print);
	ft_free((void **)&cwd_to_print);
	return (0);
}
