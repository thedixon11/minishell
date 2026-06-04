
//TODO: pas du tout bien structurer, faut encore BEAUCOUP travailler dessus !

#ifndef MINISHELL_XECUTION_H
# define MINISHELL_XECUTION_H

//NOTE: la struct t_cmd est creer uniquement dans l'execve preparation
typedef struct s_cmd
{
  char  *prog_fullname;
  char  **args_array;
  char  **path_array;
  char  **env;
} t_cmd;

//NOTE: la struct t_line est utilisee pour la liste chainee de la cmd.
// chaque node est un element de la cmd (soit cmd, pipe in, pipe out, heredoc, ...)
typedef struct s_line
{
  t_type  type;
  char  *content;
  char	**content_xpand;
  int fd;
  int cmd_nb;
  struct s_line  *prev;
  struct s_line  *next;
} t_line;

//NOTE: la struct s_env est creer au tout debut du programme par Alex.
typedef struct s_env
{
  char  *name;
  char  *content;
  struct s_env  *prev;
  struct s_env  *next;
} t_env;

//NOTE: la struct t_data est creer au tout debut du programme.
// elle va contenir des donnees utilisees globalement dans le prog.
typedef struct s_data
{
  t_env  *env;
  t_line  *line;
  int max_cmd;
  int *pipe_fd;
  int old_read_fd;
  int *heredoc_pipe_fds;
} t_data;


//NOTE: cet enum enumere les differents types de nodes possible dans la liste chainee de la cmd
typedef enum e_type
{
  T_INPUT,
  T_OUTPUT_TRUNC,
  T_OUTPUT_APPEND,
  T_HEREDOC,
  T_PIPE_IN,
  T_PIPE_OUT,
  T_COMMAND,
} t_type;

//heredoc exec function
void  heredoc_exec(t_data *data, t_line *line_cmd, t_env *env);


#endif

