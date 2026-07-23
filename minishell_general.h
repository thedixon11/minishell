#ifndef MINISHELL_GENERAL_H
# define MINISHELL_GENERAL_H
# include "./libft/libft.h"
# include "./minishell_struct.h"
# include "./src_exec/minishell_xecution.h"
# include "./src_xpand/minishell_xpansion.h"
# include "./src_builtin/minishell_builtin.h"

# define MALLOC_ERR "malloc error"
# define DUP2_ERR "dup2 error"
# define FORK_ERR "fork error"
# define PIPE_ERR "pipe error"
# define EXECVE_ERR "execve error"
# define WRITE_ERR "write error"
# define CMD_ERR "Command not found or not executable"

#endif /*MINISHELL_GENERAL_H*/
