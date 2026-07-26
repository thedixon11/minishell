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

typedef enum e_scope
{
	S_OUTSIDE,
	S_PARENT,
	S_CHILD
}					t_scope;

// NOTE: cet enum enumere les differents types de nodes possible dans la liste chainee de la cmd

typedef enum e_type
{
	T_INPUT,
	T_OUTPUT_TRUNC,
	T_OUTPUT_APPEND,
	T_HEREDOC,
	T_PIPE_IN,
	T_PIPE_OUT,
	T_COMMAND,
}					t_type;

// NOTE: la struct t_line est utilisee pour la liste chainee de la cmd.
// chaque node est un element de la cmd (soit cmd, pipe in, pipe out, heredoc,
//	...)
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

// NOTE: la struct s_env est creer au tout debut du programme par Alex.
//
typedef struct s_env
{
	char			*name;
	char			*content;
	struct s_env	*prev;
	struct s_env	*next;
}					t_env;

// NOTE: la struct t_cmd est creer uniquement dans l'execve preparation
//
typedef struct s_cmd
{
	char			*prog_fullname;
	char			**args_tab;
	char			**path_tab;
	char			**env;
}					t_cmd;

// NOTE: la struct t_data est creer au tout debut du programme.
// elle va contenir des donnees utilisees globalement dans le prog.
//
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
	char			*failed_content;
	t_cmd			cmd_data;
	int				limiter_len;
	int				saved_stdin;
	int				saved_stdout;
	char			*old_cwd;
	char			*cwd;
}					t_data;

#endif /*MINISHELL_STRUCT_H*/
