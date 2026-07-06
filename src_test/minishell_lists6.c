#include <stdalign.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../minishell_general.h"

/* ══════════════════════════════════════════════════════════════════════════════
**  T_LINE — COMMAND LINKED LIST
** ══════════════════════════════════════════════════════════════════════════════ */

static const char	*type_to_str(t_type type)
{
	const char	*names[] = {
		"T_INPUT",
		"T_OUTPUT_TRUNC",
		"T_OUTPUT_APPEND",
		"T_HEREDOC",
		"T_PIPE_IN",
		"T_PIPE_OUT",
		"T_COMMAND",
	};
	return (names[type]);
}

static t_line	*new_line_node(t_type type, const char *content, int cmd_nb)
{
	t_line	*node;

	node = malloc(sizeof(t_line));
	if (!node)
		return (NULL);
	node->type          = type;
	node->content       = content ? strdup(content) : NULL;
	node->content_xpand = NULL;
	node->fd            = -1;
	node->cmd_nb        = cmd_nb;
	node->prev          = NULL;
	node->next          = NULL;
	return (node);
}

static t_line	*append_line(t_line *head, t_line *node)
{
	t_line	*cursor;

	if (!head)
		return (node);
	cursor = head;
	while (cursor->next)
		cursor = cursor->next;
	cursor->next = node;
	node->prev   = cursor;
	return (head);
}

/*
** Builds the linked list that represents:
**
**   << EOF cat > outfile1 | sleep 5 | ls
**
**   "EOF"      → T_HEREDOC      (delimiter, cmd_nb 0 — type encodes "<<")
**   "cat"      → T_COMMAND      (cmd_nb 0, no arguments)
**   "outfile1" → T_OUTPUT_TRUNC (cmd_nb 0 — type encodes ">")
**   "|"        → T_PIPE_OUT     (cmd 0 writes into the pipe)
**   "|"        → T_PIPE_IN      (cmd 1 reads from the pipe)
**   "sleep 5"  → T_COMMAND      (cmd_nb 1)
**   "|"        → T_PIPE_OUT     (cmd 1 writes into the pipe)
**   "|"        → T_PIPE_IN      (cmd 2 reads from the pipe)
**   "ls"       → T_COMMAND      (cmd_nb 2)
*/
t_line	*build_line_list(void)
{
	t_line	*head;

	head = NULL;
	head = append_line(head, new_line_node(T_HEREDOC,      "EOF",      0));
	head = append_line(head, new_line_node(T_COMMAND,      "cat",      0));
	head = append_line(head, new_line_node(T_OUTPUT_TRUNC, "outfile1", 0));
	head = append_line(head, new_line_node(T_PIPE_OUT,     "|",        0));
	head = append_line(head, new_line_node(T_PIPE_IN,      "|",        1));
	head = append_line(head, new_line_node(T_COMMAND,      "sleep 5",  1));
	head = append_line(head, new_line_node(T_PIPE_OUT,     "|",        1));
	head = append_line(head, new_line_node(T_PIPE_IN,      "|",        2));
	head = append_line(head, new_line_node(T_COMMAND,      "ls",       2));
	return (head);
}

void	print_line_list(t_line *head)
{
	t_line	*cursor;
	int		i;

	cursor = head;
	i      = 0;
	printf("%-4s  %-16s  %-12s  %s\n", "#", "type", "content", "cmd_nb");
	printf("──────────────────────────────────────────────────\n");
	while (cursor)
	{
		printf("[%-2d]  %-16s  %-12s  %d\n",
			i,
			type_to_str(cursor->type),
			cursor->content ? cursor->content : "(null)",
			cursor->cmd_nb);
		cursor = cursor->next;
		i++;
	}
}

void	free_line_list(t_line *head)
{
	t_line	*next;

	while (head)
	{
		next = head->next;
		free(head->content);
		free(head);
		head = next;
	}
}

/* ══════════════════════════════════════════════════════════════════════════════
**  T_ENV — ENVIRONMENT LINKED LIST
** ══════════════════════════════════════════════════════════════════════════════ */

/*
** Splits one raw envp entry on the first '='.
**
**   "HOME=/Users/me"  → name="HOME"   content="/Users/me"
**   "EMPTY="          → name="EMPTY"  content=""
**   "NOEQUAL"         → name="NOEQUAL" content=NULL
*/
static t_env	*new_env_node(const char *raw)
{
	t_env		*node;
	const char	*eq;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	eq = strchr(raw, '=');
	if (eq)
	{
		node->name    = strndup(raw, eq - raw);
		node->content = strdup(eq + 1);
	}
	else
	{
		node->name    = strdup(raw);
		node->content = NULL;
	}
	if (!node->name)
	{
		free(node->content);
		free(node);
		return (NULL);
	}
	node->prev = NULL;
	node->next = NULL;
	return (node);
}

static t_env	*append_env(t_env *head, t_env *node)
{
	t_env	*cursor;

	if (!head)
		return (node);
	cursor = head;
	while (cursor->next)
		cursor = cursor->next;
	cursor->next = node;
	node->prev   = cursor;
	return (head);
}

t_env	*build_env_list(char **envp)
{
	t_env	*head;
	t_env	*node;

	if (!envp)
		return (NULL);
	head = NULL;
	while (*envp)
	{
		node = new_env_node(*envp);
		if (!node)
			return (head);
		head = append_env(head, node);
		envp++;
	}
	return (head);
}

void	print_env_list(t_env *head)
{
	t_env	*cursor;
	int		i;

	cursor = head;
	i      = 0;
	printf("%-4s  %-24s  %s\n", "#", "name", "content");
	printf("──────────────────────────────────────────────────────\n");
	while (cursor)
	{
		printf("[%-2d]  %-24s  %s\n",
			i,
			cursor->name,
			cursor->content ? cursor->content : "(null)");
		cursor = cursor->next;
		i++;
	}
}

void	free_env_list(t_env *head)
{
	t_env	*next;

	while (head)
	{
		next = head->next;
		free(head->name);
		free(head->content);
		free(head);
		head = next;
	}
}


/* ══════════════════════════════════════════════════════════════════════════════
**  DATA CREATION
** ══════════════════════════════════════════════════════════════════════════════ */

static t_data	*data_creation(t_env *env, t_line *line_cmd)
{
	t_data	*data;


	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (NULL);
	data->env = env;
	data->line_cmd = line_cmd;
	data->max_cmd_nb = 2;
	return (data);	
}


/* ══════════════════════════════════════════════════════════════════════════════
**  ENTRY POINT
** ══════════════════════════════════════════════════════════════════════════════ */

int	main(int argc, char **argv, char **envp)
{
	t_line	*line_list;
	t_env	*env_list;
	t_data	*data;
	int	code;

	(void)argc;
	(void)argv;

	/* ── command list ───────────────────────────────────────────────────── */
	printf("\n=== COMMAND LIST : << EOF cat > outfile1 | sleep 5 | ls ===\n\n");
	line_list = build_line_list();
	if (!line_list)
		return (fprintf(stderr, "Error: malloc failure (line list)\n"), 1);
	print_line_list(line_list);

	/* ── environment list ───────────────────────────────────────────────── */
	printf("\n=== ENVIRONMENT LIST ===\n\n");
	env_list = build_env_list(envp);
	if (!env_list)
		return (fprintf(stderr, "Error: malloc failure (env list)\n"), 1);
	print_env_list(env_list);


	data = data_creation(env_list, line_list);
	code = execution(data);
	//free_line_list(line_list);
	//free_env_list(env_list);

	printf("\n");
	return (code);
}
