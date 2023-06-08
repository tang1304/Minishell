/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_update.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 10:11:59 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/08 08:48:47 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	remove_node_first(t_data *data)
{
	t_lexer	*tmp;

	if (lstlen(data->lexer) == 1)
	{
		free_content_lexer_node(data->lexer);
		data->lexer = NULL;
		return ;
	}
	tmp = data->lexer;
	data->lexer = data->lexer->next;
	free_content_lexer_node(tmp);
	data->lexer->prev = NULL;
}

static void	remove_node_last(t_data *data)
{
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->prev->next = NULL;
	free_content_lexer_node(tmp);
}

static void	remove_node(t_data *data, size_t index)
{
	t_lexer	*prev;
	t_lexer	*nxt;
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp->index != index)
		tmp = tmp->next;
	prev = tmp->prev;
	nxt = tmp->next;
	prev->next = nxt;
	nxt->prev = prev;
	free_content_lexer_node(tmp);
}

void	update_lexer(t_data *data)
{
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp != NULL)
	{
		if ((tmp->word == NULL || ft_strlen(tmp->word) == 0) && \
		tmp->token == NULL)
		{
			remove_single_node(data, tmp->index);
			if (lstlen(data->lexer) == 0)
				return ;
			add_index(data);
			tmp = data->lexer;
		}
		else
			tmp = tmp->next;
	}
}

void	remove_single_node(t_data *data, size_t index)
{
	if (index == 0)
		remove_node_first(data);
	else if (index == lstlen(data->lexer) - 1)
		remove_node_last(data);
	else
		remove_node(data, index);
}
