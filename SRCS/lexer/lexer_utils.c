/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/09 09:44:37 by tgellon           #+#    #+#             */
/*   Updated: 2023/06/09 13:33:13 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

int	quote_handling(char *str, int i, char quote)
{
	int	j;

	j = 1;
	while (str[i + j] && str[i + j] != quote)
		j++;
	return (j);
}

static t_lexer	*new_lexer_node(char *str, int token)
{
	t_lexer	*node;

	node = (t_lexer *)malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	ft_bzero(node, sizeof(t_lexer));
	if (token == 0)
	{
		if (config_node(str, node, 0) != SUCCESS)
			return (free(node), NULL);
	}
	else
	{
		if (config_node(str, node, 1) != SUCCESS)
			return (free(node), NULL);
	}
	return (node);
}

int	add_node(t_lexer **lexer, char *str, int token)
{
	t_lexer	*new;
	t_lexer	*tmp;

	new = new_lexer_node(str, token);
	if (!new)
		return (0);
	if (!*lexer)
	{
		*lexer = new;
		return (1);
	}
	tmp = *lexer;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
	return (1);
}

void	add_index(t_data *data)
{
	size_t	i;
	int		change;
	t_lexer	*tmp;

	i = 0;
	tmp = data->lexer;
	while (tmp != NULL)
	{
		change = 0;
		if (tmp->index == data->svd_index)
			change = 1;
		tmp->index = i;
		if (change == 1)
			data->svd_index = tmp->index;
		i++;
		tmp = tmp->next;
	}
	data->max_index = i;
	if (i > INT_MAX)
		ft_putstr_fd("minishell: Command too long.\n", 0);
}
