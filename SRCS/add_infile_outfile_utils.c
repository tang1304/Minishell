/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_infile_outfile_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:27:51 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/27 15:24:58 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

static void	add_file_node(t_data *data, t_lexer *lexer, char *file, int i)
{
	if (i == 0)
		lexer->infile = ft_strdup(file);
	else
	{
		if (lexer->LIMITER != NULL)
			free(lexer->LIMITER);
		lexer->LIMITER = ft_strdup(file);
		data->heredoc = 1;
	}
}

void	add_infile(t_data *data, char *file, int i)
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
			{
				free(tmp->infile);
				tmp->infile = NULL;
			}
			// if (tmp->LIMITER != NULL)
			// {
			// 	free(tmp->LIMITER);
			// 	tmp->LIMITER = NULL;
			// }
			add_file_node(data, tmp, file, i);
			return ;
		}
		tmp = tmp->next;
	}
}

void	add_outfile(t_data *data, char *file)
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
		tmp = tmp->prev; //<TODO >out ls | wc -l >>append marche
	}
}

size_t	lstlen(t_lexer *lexer)
{
	size_t	len;
	t_lexer	*tmp;

	len = 0;
	if (!lexer)
		return (0);
	tmp = lexer;
	while (tmp != NULL)
	{
		len++;
		tmp = tmp->next;
	}printf("lstlen: %ld\n", len);
	return (len);
}
