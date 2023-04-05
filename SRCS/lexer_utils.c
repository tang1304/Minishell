/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:50:54 by tgellon           #+#    #+#             */
/*   Updated: 2023/04/05 08:36:56 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
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
		node->word.name = ft_strdup(str);
		node->word.infile = NULL;
		node->word.outfile = NULL;
		node->token.name = NULL;
		printf("word: %s\n", node->word.name);
	}
	else
	{
		node->word.name = NULL;
		node->token.name = ft_strdup(str);
		printf("token: %s\n", node->token.name);
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
