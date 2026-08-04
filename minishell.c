#include "alex.h"

int	main()
{
	char	*line;
	t_token	*token;
	t_line	*lines;

	while (1)
	{
		line = readline("minishell$ ");	// -lreadline pour compil
		add_history(line);				// historique envoie au prompt fleche du haut et du bas pour check
		token = to_token(line);
		lines = to_parse(token);
		// print_tokens(token);
		print_lines(lines);
		if (!line)
			break ;						//renvoie NULL ctrl D to leave
	}
		return (0);
}

int	print_tokens(t_token *token)
{
	while (token != NULL)
	{
		printf("value = %s, et type = %u\n", token->value, token->type);
		token = token->next;
	}
	return (0);
}

int	print_lines(t_line *lines)
{
	while (lines != NULL)
	{
		printf("content = %s, type = %d, et cmd = %d\n", lines->content, lines->type, lines->cmd_nb);
		lines = lines->next;
	}
	return (0);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	lensrc;

	lensrc = ft_strlen(src);
	i = 0;
	if (size == 0)
		return (lensrc);
	while (i < size -1 && src[i] != 0)
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (lensrc);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*ptr;
	unsigned char	*ptr1;

	ptr1 = (unsigned char *)src;
	ptr = (unsigned char *)dest;
	if (!dest && !src)
		return (dest);
	while (n > 0)
	{
		*ptr = *ptr1;
		ptr++;
		ptr1++;
		n--;
	}
	return (dest);
}