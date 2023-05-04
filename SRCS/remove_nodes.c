/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:41:23 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/18 18:41:23 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	remove_front_nodes(t_data *data)
{
	t_lexer	*tmp;

	tmp = data->lexer;
	data->lexer = tmp->next;
	data->lexer->prev = NULL;
	tmp->next = NULL;
	tmp->token = NULL;
	free(tmp);
	tmp = data->lexer;
	if (tmp->next != NULL)
	{
		data->lexer = tmp->next;
		data->lexer->prev = NULL;
		tmp->next = NULL;
	}
	else
		data->lexer = NULL;
	tmp->word = NULL;
	free(tmp);
}

void	remove_back_nodes(t_data *data)
{
	t_lexer	*tmp;
	int		count;

	count = 2;
	while (count > 0)
	{
		tmp = data->lexer;
		while (tmp->next != NULL)
			tmp = tmp->next;
		if (tmp->next != NULL)
			tmp->next = NULL;
		tmp->prev->next = NULL;
		if (tmp->prev != NULL)
			tmp->prev = NULL;
		if (tmp->word != NULL)
			tmp->word = NULL;
		if (tmp->token != NULL)
			tmp->token = NULL;
		free(tmp);
		count--;
	}
}

void	remove_middle_nodes(t_data *data, size_t index)
{
	t_lexer	*rm1;
	t_lexer	*rm2;
	t_lexer	*tmp1;
	t_lexer	*tmp2;

	rm1 = data->lexer;
	while (rm1->index != index)
		rm1 = rm1->next;
	rm2 = rm1->next;
	tmp1 = rm1->prev;
	tmp2 = rm2->next;
	tmp1->next = tmp2;
	tmp2->prev = tmp1;
	rm1->prev = NULL;
	rm1->next = NULL;
	free(rm1->token);
	rm1->token = NULL;
	rm2->prev = NULL;
	rm2->next = NULL;
	free(rm2->word);
	rm2->word = NULL;
	free(rm1);
	free(rm2);
}
