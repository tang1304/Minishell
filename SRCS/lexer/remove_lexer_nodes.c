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
// A revoir pour ne pas segf dans le cas ou <TODO |>out

void	free_content_lexer_node(t_lexer *tmp)
{
	if (tmp->word != NULL)
		free(tmp->word);
	if (tmp->token != NULL)
		free(tmp->token);
	if (tmp->infile != NULL)
		free(tmp->infile);
	if (tmp->outfile != NULL)
		free(tmp->outfile);
	tmp->word = NULL;
	tmp->token = NULL;
	tmp->prev = NULL;
	tmp->next = NULL;
	free(tmp);
	tmp = NULL;
}

void	free_lst(t_data *data, t_lexer *tmp)
{
	data->lexer = data->lexer->next;
	free_content_lexer_node(tmp);
	if (data->lexer->word != NULL)
		free(data->lexer->word);
	data->lexer->word = NULL;
	if (data->lexer->token != NULL)
		free(data->lexer->token);
	data->lexer->token = NULL;
	data->lexer->prev = NULL;
	data->lexer->next = NULL;
	free(data->lexer);
	data->lexer = NULL;
}

void	remove_front_nodes(t_data *data, size_t len)
{

	t_lexer	*tmp;

	tmp = data->lexer;
	if (len == 2)
	{
		free_lst(data, tmp);
		return ;
	}
	data->lexer = tmp->next;
	free_content_lexer_node(tmp);
	tmp = data->lexer;
	data->lexer = tmp->next;
	data->lexer->prev = NULL;
	if (tmp->fdin)
		close(tmp->fdin);
	if (tmp->fdout)
		close(tmp->fdout);
	free_content_lexer_node(tmp);
}

void	remove_back_nodes(t_data *data)
{
	t_lexer	*tmp;
	int		times;

	times = 2;
	while (times > 0)
	{
		tmp = data->lexer;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->prev->next = NULL;
		if (tmp->fdin)
			close(tmp->fdin);
		if (tmp->fdout)
			close(tmp->fdout);
		free_content_lexer_node(tmp);
		times--;
	}


	// int		count;

	// count = 2;
	// while (count > 0)
	// {
	// 	tmp = data->lexer;
	// 	while (tmp->next != NULL)
	// 		tmp = tmp->next;
	// 	if (tmp->next != NULL)
	// 		tmp->next = NULL;
	// 	tmp->prev->next = NULL;
	// 	if (tmp->prev != NULL)
	// 		tmp->prev = NULL;
	// 	if (tmp->word != NULL)
	// 		tmp->word = NULL;
	// 	if (tmp->token != NULL)
	// 		tmp->token = NULL;
	// 	free(tmp);
	// 	count--;
	// }
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
