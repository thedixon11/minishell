#ifndef MINISHELL_GENERAL_H
# define MINISHELL_GENERAL_H
# include "./libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "./minishell_struct.h"
# include "./src_parsing/minishell_parsing.h"
# include "./src_exec/minishell_xecution.h"
# include "./src_xpand/minishell_xpansion.h"
# include "./src_builtin/minishell_builtin.h"
# include "./src_heredoc/minishell_heredoc.h"
# include "./src_errors/minishell_errors.h"

// List of items
# define I_CALLOC "ft_calloc"
# define I_STRJOIN "ft_strjoin"
# define I_SPLIT "ft_split"
# define I_STRDUP "ft_strdup"
# define I_PRINTF "ft_printf"
# define I_STRSRRND "ft_strsrrnd"
# define I_STRTRIM "ft_strtrim"
# define I_SUBSTR "ft_substr"
# define I_ARRAYDUP "ft_arraydup"
# define I_PUTENDL_FD "ft_putendl_fd"
# define I_ITOA "ft_itoa"
# define I_GNL "get_next_line"
# define I_DUP "dup"
# define I_DUP2 "dup2"
# define I_WRITE "write"
# define I_PIPE "pipe"
# define I_EXECVE "execve"
# define I_FORK "fork"
# define I_ECHO "echo"
# define I_CD "cd"
# define I_ENV "env"
# define I_EXIT "exit"
# define I_EXPORT "export"
# define I_PWD "pwd"
# define I_UNSET "unset"
# define I_STAT "stat"

// List of error messages
# define LIBFT_ERR "Libft function execution failed"
# define NOFILE_ERR "No such file or directory"
# define CMD_ERR "command not found"
# define AMB_REDIR_ERR "amgiguous redirect"
# define CD_ARGS_ERR "too many arguments"
# define CD_NO_HOME "HOME not set"
# define ENV_ARGS_ERR "too many arguments"
# define EXIT_INVALID "numeric argument required"
# define EXIT_ARGS_ERR "too many arguments"
# define EXPORT_ID_ERR "not a valid identifier"
# define DIR_ERR "Is a directory"

#endif /*MINISHELL_GENERAL_H*/
