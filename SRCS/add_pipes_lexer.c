/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_pipes_lexer.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 15:11:37 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/05 15:50:02 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	add_pipes_redir(t_data *data)
{
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp != NULL)
	{
		if (tmp->prev != NULL && tmp->prev->token != NULL && \
		ft_strncmp(tmp->prev->token, "|", 1) == 0)
			tmp->pipe_b = 1;
		if (tmp->next != NULL && tmp->next->token != NULL && \
		ft_strncmp(tmp->next->token, "|", 1) == 0)
			tmp->pipe_a = 1;
		tmp = tmp->next;
	}
}
