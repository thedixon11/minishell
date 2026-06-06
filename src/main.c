#include "minishell_xpansion.h"

void	free_all(t_data *data)
{
	t_env	*del_env;
	t_line	*del_line;

	del_env = data->env;
	while (del_env->next != NULL)
	{
		free(del_env->name);
		free(del_env->content);
		del_env = del_env->next;
		free(del_env->prev);
	}
	free(del_env->name);
	free(del_env->content);
	free(del_env);

	del_line = data->line;
	while (del_line->next != NULL)
	{
		free(del_line->content);
		ft_free_tab(del_line->content_xpand);
		del_line = del_line->next;
		free(del_line->prev);
	}
	free(del_line->content);
	ft_free_tab(del_line->content_xpand);
	free(del_line);
	free(data);
}

void  print_content(char **content)
{
  int y;

  y = 0;
  while (content[y] != NULL)
  {
    ft_printf("%s\n", content[y]);
    y++;
  }
  ft_printf("\n\n");
}

t_env *create_env(void)
{
  t_env *node1;
  t_env *node2;
  t_env *node3;
  t_env *node4;

  node1 = ft_calloc(1, sizeof(t_env));
  node2 = ft_calloc(1, sizeof(t_env));
  node3 = ft_calloc(1, sizeof(t_env));
  node4 = ft_calloc(1, sizeof(t_env));
  node1->prev = NULL;
  node1->next = node2;
  node2->prev = node1;
  node2->next = node3;
  node3->prev = node2;
  node3->next = node4;
  node4->prev = node3;
  node4->next = NULL;

  node1->name = ft_strdup("CA");
  node1->content = ft_strdup("c");
  node2->name = ft_strdup("PI");
  node2->content = ft_strdup("a");
  node3->name = ft_strdup("BARA");
  node3->content = ft_strdup("t file1");
  node4->name = ft_strdup("SHIT");
  node4->content = ft_strdup("");
  return (node1);
}

t_line  *create_cmd_line(void)
{
  t_line  *node1;
  t_line  *node2;
  node1 = ft_calloc(1, sizeof(t_line));
  node2 = ft_calloc(1, sizeof(t_line));
  node1->prev = NULL;
  node1->next = node2;
  node2->prev = node1;
  node2->next = NULL;

  node1->type = T_INPUT;
  node1->content = ft_strdup("file2 \"$SHIT\"");
  node1->cmd_nb = 0;
  node2->type = T_COMMAND;
  node2->content = ft_strdup("$CA$PI\"$BARA\"");
  node2->cmd_nb = 0;
  return (node1);
}

t_data  *create_data(void)
{
  t_data  *data;

  data = ft_calloc(1, sizeof(t_data));
  data->env = create_env();
  data->line = create_cmd_line();
  return (data);
}

int main(void)
{
  t_data  *data;
  t_line  *current;
  int y;

  y = 0;
  data = create_data();
  val_manager(data, data->line);
  current = data->line;
  while (current != NULL)
  {
    print_content(current->content_xpand);
    current = current->next;
  }
	free_all(data);
  return (0);
}

