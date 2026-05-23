
//TODO: pas du tout bien structurer, faut encore BEAUCOUP travailler dessus !

#ifndef MINISHELL_XECUTION_H
# define MINISHELL_XECUTION_H

typedef struct s_cmd
{
  char  *prog_fullname;
  char  **args_array;
  char  **path_array;
  char  **env;
} t_cmd;

typedef struct s_line
{
  t_type  type;
  char  *content;
  int fd;
  int cmd_nb;
  struct s_line  *prev;
  struct s_line  *next;
} t_line;

typedef struct s_env
{
  char  *name;
  char  *content;
  struct s_env  *prev;
  struct s_env  *next;
} t_env;

typedef struct s_data
{
  t_env  *env;
  t_line  *line;
  int max_cmd;
  int *pipe_fd;
  int old_read_fd;
  int *heredoc_pipe_fds;
  char  **cmd_array;
} t_data;

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

