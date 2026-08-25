#ifndef MINISHELL_STRUCT_H
# define MINISHELL_STRUCT_H

typedef enum e_quote
{
	Q_NONE,
	Q_SINGLE,
	Q_DOUBLE,
	Q_HEREDOC
}					t_quote;

typedef enum e_bool
{
	B_FALSE,
	B_TRUE
}					t_bool;

typedef enum e_type
{
	T_INPUT,
	T_OUTPUT_TRUNC,
	T_OUTPUT_APPEND,
	T_HEREDOC,
	T_PIPE_IN,
	T_PIPE_OUT,
	T_COMMAND,
	T_PIPE
}					t_type;

typedef struct s_line
{
	t_type			type;
	char			*content;
	char			**content_xpand;
	int				fd;
	int				*fd_of_pipe;
	int				cmd_nb;
	struct s_line	*prev;
	struct s_line	*next;
}					t_line;

typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

typedef struct s_cmd
{
	char			*prog_fullname;
	char			**args_tab;
	char			**path_tab;
	char			**env;
}					t_cmd;

typedef struct s_token
{
	char			*value;
	t_type			type;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_state
{
	int				start;
	char			*str;
	int				i;
	char			quote;
}					t_state;

typedef struct s_data
{
	t_env			*env;
	t_line			*line_cmd;
	int				current_cmd_nb;
	int				max_cmd_nb;
	int				pipe_fd[2];
	int				old_read_fd;
	int				heredoc_pipe_fds[2];
	int				wstatus;
	int				saved_errno;
	int				error;
	int				code;
	int				last_code;
	char			*failed_content;
	t_cmd			*cmd_data;
	int				limiter_len;
	int				saved_stdin;
	int				saved_stdout;
	t_bool			do_i_exit;
	char			*old_cwd;
	char			*cwd;
	int				last_pid;
	t_token			*token_head;
}					t_data;

#endif
