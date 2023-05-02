/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_infile_outfile_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:27:51 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/02 11:07:07 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
//ls <TODO | wc <Makefile >outer | test >out working fiiiiiiine !!!!!
static void	add_file_node(t_data *data, t_lexer *lexer, char *file, int i)
{
	if (i == 0)
		lexer->infile = ft_strdup(file);
	else
	{
		data->hd->LIMITER[data->hd->heredoc] = ft_strdup(file);
		data->hd->heredoc++;
		data->hd->hd_as_inf = 1;
	}
}

static t_lexer	*find_start(t_lexer *tmp)
{
	while (tmp->prev != NULL)
	{
		if (tmp->word != NULL && tmp->prev != NULL)
			tmp = tmp->prev;
		else if (ft_strncmp(tmp->token, "|", 1) != 0 && tmp->token != NULL)
			tmp = tmp->prev;
		else
			break ;
	}
	if (tmp->word == NULL)
		tmp = tmp->next;
	return (tmp);
}

void	add_infile(t_data *data, char *file, size_t index, int i)
{
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp->index != index)
		tmp = tmp->next;
	tmp = find_start(tmp);
	while (tmp != NULL)
	{
		if (tmp->token != NULL && ft_strncmp(tmp->token, "|", 1) == 0)
			break ;
		if ((tmp->word != NULL && tmp->prev == NULL) || (tmp->word != NULL \
		&& tmp->prev->word != NULL) || (tmp->word != NULL && \
		ft_strncmp(tmp->prev->token, "|", 1) == 0))
		{
			if (tmp->infile != NULL)
			{
				free(tmp->infile);
				tmp->infile = NULL;
				data->hd->hd_as_inf = 0;
			}
			add_file_node(data, tmp, file, i);
			return ;
		}
		tmp = tmp->next;
	}
}

void	add_outfile(t_data *data, char *file, size_t index)
{
	t_lexer	*tmp;

	tmp = data->lexer;
	while (tmp->index != index)
		tmp = tmp->next;
	tmp = find_start(tmp);
	while (tmp != NULL)
	{
		if (tmp->token != NULL && ft_strncmp(tmp->token, "|", 1) == 0)
			break ;
		if ((tmp->word != NULL && tmp->prev == NULL) || (tmp->word != NULL \
		&& tmp->prev->word != NULL) || (tmp->word != NULL && \
		ft_strncmp(tmp->prev->token, "|", 1) == 0))
		{
			if (tmp->outfile != NULL)
	 			free(tmp->outfile);
	 		tmp->outfile = ft_strdup(file);
			return ;
		}
		tmp = tmp->next;
	}
}
