#ifndef MINISHELL_GENERAL_H
# define MINISHELL_GENERAL_H
# include "./libft/libft.h"
# include "./minishell_struct.h"
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
# define I_GNL "get_next_line"
# define I_DUP "dup"
# define I_DUP2 "dup2"
# define I_WRITE "write"
# define I_PIPE "pipe"
# define I_EXECVE "execve"
# define I_FORK "fork"

// List of error messages
# define LIBFT_ERR "function execution failed"
# define CMD_ERR "Command not found"
# define AMB_REDIR_ERR "Amgiguous redirect"

#endif /*MINISHELL_GENERAL_H*/
