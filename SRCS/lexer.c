/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgellon <tgellon@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:45:15 by tgellon           #+#    #+#             */
/*   Updated: 2023/03/29 17:13:57 by tgellon          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

t_lexer	*new_lexer_node(t_lexer *lexer, char *str, int token)
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
}

int	lexer_init(t_data *data)
{
	int		i;
	int		j;
	char	**words;

	i = 0;
	words = ft_split(data->str, ' ');
	if (!words)
		;
	while (words[i])
	{
		j = 0;
		while (data->tokens_tab[j])
		{
			if (ft_strncmp(words[i], data->tokens_tab[j], ft_strlen(words[i])) == 0)
				add_node(data->lexer, words[i], 1);
			else
				j++;
		}
		add_node(data->lexer, words[i], 0);
		i++;
	}
}
