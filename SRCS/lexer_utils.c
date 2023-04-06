/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:50:54 by tgellon           #+#    #+#             */
/*   Updated: 2023/04/04 11:09:06 by rrebois          ###   ########lyon.fr   */
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
	static int	i;
	t_lexer		*node;

	node = (t_lexer *)malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	node->index = i;
	i++;
	if (token == 0)
	{
		node->word = ft_strdup(str);
		node->token = NULL;
		//printf("word: %s\n", node->word);
	}
	else
	{
		node->word = NULL;
		node->token = ft_strdup(str);
		//printf("token: %s\n", node->token);
	}
	node->next = NULL;
	node->prev = NULL;
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
