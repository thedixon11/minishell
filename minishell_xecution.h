
//TODO: pas du tout bien structurer, faut encore BEAUCOUP travailler dessus !

#ifndef MINISHELL_XECUTION_H
# define MINISHELL_XECUTION_H

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
  int max_cmd_nb;
  int *pipe_fd;
  int old_read_fd;
  int *heredoc_pipe_fds;
} t_data;

// execution functions
void	*execution(t_data *data, t_line *line_cmd, t_env *env);
void	execute_cmds(t_data *data, t_line *line_cmd, t_env *env);
void	open_fd_in_line_cmd(t_data *data, t_line *line_cmd, int current_cmd_nb);
void	parent_process(t_data *data, int current_cmd_nb);
void	child_process(t_data *data, t_line *line_cmd, int current_cmd_nb);

//heredoc functions

void	heredoc_exec(t_data *data, t_line *line_cmd);
void create_heredoc_fd(t_data *data, t_line *heredoc);
void  write_on_fd(t_data *data, t_line *heredoc, t_bool xpand_or_not);
char  *expand_line_hdoc(char *line, t_bool xpand_or_not);
char  *go_until_dollar_hdoc(char *line, int *start);

//check in and out redirections
int	check_in_out_redir(t_line *cmd_line);

// environment convertert from linked list to env_converter_ll_to_array
char	**env_converter_ll_to_array(t_env *env);
char	*rebuild_value(t_env *current);

// preparation of material before execve

t_cmd	*execve_preparation(t_data *data, char **cmd_content);
char	*create_prog_fullname(char **path_array, char *prog_name);
char	**create_path_array(t_env *env);
int	is_binary_existing_and_executable(char *path_to_check);

#endif

