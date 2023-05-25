/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_lexer_nodes_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:35:04 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/22 10:35:04 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	remove_lxr_node(t_data *data, size_t index)
{
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp->index != index)
		tmp = tmp->next;
	free(tmp->word);
	if (lstlen(data->lexer) > 1)
	{
		tmp->prev->next = NULL;
		tmp->prev = NULL;
	}
	free(tmp);
	tmp = NULL;
	if (lstlen(data->lexer) == 1)
		data->lexer = NULL;
}
