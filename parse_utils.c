#include "alex.h"

t_line	*new_line(t_type type, int cmd_nb, char *content)
{
	t_line	*node;

	node = calloc(1, sizeof(t_line));
	if (!node)
		return (NULL);
	node->type = type;
	node->fd = -1;
	node->cmd_nb = cmd_nb;
	node->content = content;
	return (node);
}

void	add_line(t_line *current, t_line **head)
{
	t_line	*temp;

	if (*head == NULL)
		*head = current;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		current->next = NULL;
		current->prev = temp;
		temp->next = current;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	ls1;
	size_t	ls2;
	size_t	lenstr;

	ls1 = ft_strlen(s1);
	ls2 = ft_strlen(s2);
	lenstr = ls1 + ls2 +1;
	if (s1 == 0)
		return ((char *)s2);
	if (s2 == 0)
		return ((char *)s1);
	str = calloc(lenstr, sizeof(char));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s1, ls1 + 1);
	ft_strlcat(str, s2, lenstr);
	return (str);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	lendst;
	size_t	lensrc;

	lendst = ft_strlen(dst);
	lensrc = ft_strlen(src);
	if (size <= lendst)
		return (size + lensrc);
	if (lensrc < size - lendst)
		ft_memcpy(dst + lendst, src, lensrc + 1);
	else
	{
		ft_memcpy(dst + lendst, src, size - lendst - 1);
		dst[size - 1] = '\0';
	}
	return (lensrc + lendst);
}
