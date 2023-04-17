/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_infile_outfile_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:27:51 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/17 15:27:51 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

void	add_infile(t_data *data, char *file) // seems OK
{
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp != NULL)
	{
		if ((tmp->word != NULL && tmp->prev == NULL) || (tmp->word != NULL \
		&& tmp->prev->word != NULL) || (tmp->word != NULL && \
		ft_strncmp(tmp->prev->token, "|", 1) == 0))
		{
			if (tmp->infile != NULL)
				free(tmp->infile);//dqtq limiter = NULL hdoc = 0
			tmp->infile = ft_strdup(file);
			return ;
		}
		tmp = tmp->next;
	}
}

void	add_outfile(t_data *data, char *file) //not working well we have 1 word node with nothign at the end +
{
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp->next != NULL)
		tmp = tmp->next;
	while (tmp != NULL)
	{
		if ((tmp->word != NULL && tmp->prev == NULL) || (tmp->word != NULL \
		&& tmp->prev->word != NULL && tmp->prev != NULL) || \
		(tmp->word != NULL && tmp->prev != NULL && \
		ft_strncmp(tmp->prev->token, "|", 1) == 0))
		{
			if (tmp->outfile != NULL)
				free(tmp->outfile);
			tmp->outfile = ft_strdup(file);
			return ;
		}
		tmp = tmp->prev; //<TODO >out ls | wc -l >>append

	}
}
