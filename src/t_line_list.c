#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ─── Types ──────────────────────────────────────────────────────────────── */

typedef enum e_type
{
	T_INPUT,
	T_OUTPUT_TRUNC,
	T_OUTPUT_APPEND,
	T_HEREDOC,
	T_PIPE_IN,
	T_PIPE_OUT,
	T_COMMAND,
}	t_type;

typedef struct s_line
{
	t_type			type;
	char			*content;
	char			**content_xpand;
	int				fd;
	int				cmd_nb;
	struct s_line	*prev;
	struct s_line	*next;
}	t_line;

/* ─── Helpers ─────────────────────────────────────────────────────────────── */

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

/* ─── Core list operations ────────────────────────────────────────────────── */

/*
** Allocates and initialises a new node.
** content_xpand and fd are intentionally left at their zero-value defaults.
*/
static t_line	*new_node(t_type type, const char *content, int cmd_nb)
{
	t_line	*node;

	node = malloc(sizeof(t_line));
	if (!node)
		return (NULL);
	node->type         = type;
	node->content      = content ? strdup(content) : NULL;
	node->content_xpand = NULL;   /* not filled – spec */
	node->fd           = -1;      /* not filled – spec  */
	node->cmd_nb       = cmd_nb;
	node->prev         = NULL;
	node->next         = NULL;
	return (node);
}

/*
** Appends a node at the tail of the list.
** Returns the list head (unchanged after the first node).
*/
static t_line	*append(t_line *head, t_line *node)
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

/* ─── Builder ─────────────────────────────────────────────────────────────── */

/*
** Builds the linked list that represents:
**
**   < infile1  cat  |  wc -l  > outfile1
**
** Token breakdown (left → right):
**
**   "infile1"  → T_INPUT        (type already encodes "<", no operator node)
**   "cat"      → T_COMMAND      (cmd_nb 0)
**   "|"        → T_PIPE_OUT     (right side of pipe for cmd 0)
**              → T_PIPE_IN      (left  side of pipe for cmd 1)
**   "wc -l"    → T_COMMAND      (cmd_nb 1)
**   "outfile1" → T_OUTPUT_TRUNC (type already encodes ">", no operator node)
**
** NOTE: The pipe is split into two nodes (PIPE_OUT / PIPE_IN) so that each
** command boundary is explicit and easy to walk from either direction.
*/
static t_line	*build_list(void)
{
	t_line	*head;

	head = NULL;

	/* ── command 0 : < infile1  cat ─────────────────────────────────────── */

	/* T_INPUT carries the "<" semantic — no operator node needed */
	head = append(head, new_node(T_INPUT, "infile1", 0));

	head = append(head, new_node(T_COMMAND, "cat", 0));

	/* ── pipe boundary ──────────────────────────────────────────────────── */

	/* cmd 0 writes INTO the pipe */
	head = append(head, new_node(T_PIPE_OUT, "|", 0));

	/* cmd 1 reads FROM the pipe */
	head = append(head, new_node(T_PIPE_IN, "|", 1));

	/* ── command 1 :  wc -l  > outfile1 ────────────────────────────────── */

	head = append(head, new_node(T_COMMAND, "wc -l", 1));

	/* T_OUTPUT_TRUNC carries the ">" semantic — no operator node needed */
	head = append(head, new_node(T_OUTPUT_TRUNC, "outfile1", 1));

	return (head);
}

/* ─── Debug printer ───────────────────────────────────────────────────────── */

static void	print_list(t_line *head)
{
	t_line	*cursor;
	int		i;

	cursor = head;
	i      = 0;
	printf("%-3s  %-16s  %-12s  %s\n",
		"#", "type", "content", "cmd_nb");
	printf("─────────────────────────────────────────────\n");
	while (cursor)
	{
		printf("[%-1d]  %-16s  %-12s  %d\n",
			i,
			type_to_str(cursor->type),
			cursor->content ? cursor->content : "(null)",
			cursor->cmd_nb);
		cursor = cursor->next;
		i++;
	}
}

/* ─── Cleanup ─────────────────────────────────────────────────────────────── */

static void	free_list(t_line *head)
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

/* ─── Entry point ─────────────────────────────────────────────────────────── */

int	main(void)
{
	t_line	*list;

	list = build_list();
	if (!list)
	{
		fprintf(stderr, "Error: malloc failure\n");
		return (1);
	}
	printf("\nCommand : < infile1 cat | wc -l > outfile1\n\n");
	print_list(list);
	printf("\n");
	free_list(list);
	return (0);
}
