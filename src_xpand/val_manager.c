/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   val_manager.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jvasconc <jvasconc@student.42lausanne.ch>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/25 15:15:53 by jvasconc          #+#    #+#             */
/*   Updated: 2026/08/25 15:16:25 by jvasconc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell_general.h"

char	*expand_in_quote(t_data *data, char *row)
{
	char	*first;
	char	*second;
	int		i;

	i = 0;
	second = NULL;
	first = ft_strdup("");
	if (!first)
		return (error_char(data, I_STRDUP, LIBFT_ERR, 1));
	while (row[i] != 0 && first != NULL)
	{
		if (row[i] != '"' && row[i] != '\'')
			second = go_until_quote(data, row, &i);
		else if (row[i] == '"' || row[i] == '\'')
			second = quote_manager(data, row, &i, row[i]);
		if (second != NULL)
			first = fusion_first_second_block(data, first, second);
		else
			return (ft_free((void **)first), NULL);
	}
	return (first);
}

char	*expand_off_quote(t_data *data, char *content)
{
	char	*first;
	char	*second;
	int		i;

	i = 0;
	second = NULL;
	first = ft_strdup("");
	if (!first)
		return (error_char(data, I_STRDUP, LIBFT_ERR, 1));
	while (content[i] != 0 && first != NULL)
	{
		if (content[i] != 0 && content[i] != '$')
			second = go_until_dollar(data, content, &i);
		else if (content[i] == '$')
			second = dollar_manager(data, content, &i, Q_NONE);
		if (second != NULL)
			first = fusion_first_second_block(data, first, second);
		else
			return (ft_free((void **)&first), NULL);
	}
	return (first);
}

int	content_splitted_manager(t_data *data, char **content_to_xpand)
{
	int		y;
	char	*temp;

	y = 0;
	temp = NULL;
	while (content_to_xpand[y] != NULL)
	{
		temp = ft_strdup(content_to_xpand[y]);
		if (!temp)
			return (error_int(data, I_STRDUP, LIBFT_ERR, 1));
		ft_free((void **)&content_to_xpand[y]);
		content_to_xpand[y] = expand_in_quote(data, temp);
		ft_free((void **)&temp);
		if (!content_to_xpand[y])
			return (1);
		y++;
	}
	return (0);
}

char	*manage_before_split(t_data *data, char *content)
{
	char	*temp1;
	char	*temp2;

	temp2 = NULL;
	temp1 = expand_off_quote(data, content);
	if (!temp1)
		return (NULL);
	temp2 = ft_strtrim(temp1, " ");
	ft_free((void **)&temp1);
	if (!temp2)
		return (error_char(data, I_STRTRIM, LIBFT_ERR, 1));
	return (temp2);
}

int	val_manager(t_data *data)
{
	char	*temp;
	t_line	*current;

	current = data->line_cmd;
	while (current != NULL)
	{
		if (current->type == T_INPUT || current->type == T_OUTPUT_TRUNC
			|| current->type == T_OUTPUT_APPEND || current->type == T_COMMAND)
		{
			temp = manage_before_split(data, current->content);
			if (!temp)
				return (1);
			if (temp[0] == 0)
				return (ft_free((void **)&temp), 0);
			current->content_xpand = ft_split_quote(temp, ' ');
			ft_free((void **)&temp);
			if (!current->content_xpand)
				return (error_int(data, I_SPLIT, LIBFT_ERR, 1));
			if (content_splitted_manager(data, current->content_xpand) == 1)
				return (1);
		}
		current = current->next;
	}
	return (0);
}
