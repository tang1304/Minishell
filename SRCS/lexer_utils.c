/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 08:50:54 by tgellon           #+#    #+#             */
/*   Updated: 2023/03/30 11:05:10 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static t_lexer	*new_lexer_node(t_lexer *lexer, char *str, int token)
{
	t_lexer	*node;

	node = (t_lexer *)malloc(sizeof(t_lexer));
	if (!node)
		return (NULL);
	if (!node->prev)
		node->index = 0;
	else
		node->index = node->prev->index + 1;
	if (token == 0)
	{
		node->word.name = str;
		node->token.name = NULL;
	}
	else
	{
		node->word.name = NULL;
		node->token.name = str;
	}
	node->next = NULL;
	node->prev = NULL;
	return (node);
}

void	*add_node(t_lexer *lexer, char *str, int token)
{
	t_lexer	*new;
	t_lexer	*tmp;

	new = new_lexer_node(lexer, str, token);
	if (!new)
		return (NULL);
	if (!lexer)
	{
		lexer = new;
		return ;
	}
	tmp = lexer;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
	new->prev = tmp;
}
