/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/12 14:37:02 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/22 16:12:33 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

// si on spam <<a<<b<<c<<d au bout d'un moment ./minishell se ferme
#include "../incs/minishell.h"

void	heredoc_redir(t_data *data)
{
	t_lexer	*tmp;

	heredoc_count(data);
printf("IN THIS LINE WE HAVE %d HREDOCS\n", data->hd->hd_count);
	tmp = data->lexer;
	while (tmp != NULL)
	{
		if (tmp->token != NULL && ft_strncmp(tmp->token, "<<", 2) == 0 \
		&& ft_strlen(tmp->token) == 2)
		{
			data->hd->LIMITER[data->hd->heredoc] = ft_strdup(tmp->next->word);
			data->hd->heredoc++;
		}
		tmp = tmp->next;
	}
	data->hd->heredoc = 0;
	init_heredoc_data(data);





	// test ls<<a<<b<Makefile
// 	if (lstlen(data->lexer) > 0)
// 	{
// 	size_t len = 0;
// 	tmp = data->lexer;
// 	while (tmp != NULL)
// 	{
// 		len++;
// 		tmp = tmp->next;
// 	}
// 	printf("len: %ld\n", len);


// 	t_data	*tmp2;
// 	tmp2 = data;
// 	while (tmp2->lexer != NULL)
// 	{
// 		ft_printf("\n\n");
// if (tmp2->lexer->word != NULL)
// 	ft_printf("word node: %s\n", tmp2->lexer->word);
// else
// 	ft_printf("token node: %s\n", tmp2->lexer->token);
// printf("index: %ld\n", tmp2->lexer->index);
// ft_printf("infile: %s\n", tmp2->lexer->infile);
// ft_printf("outfile: %s\n", tmp2->lexer->outfile);
// ft_printf("hdoc: %d\n",tmp2->lexer->hd_file);
// ft_printf("hdoc count: %d\n",tmp2->hd->hd_count);
// 		tmp2->lexer = tmp2->lexer->next;
// 	}}
// 	// end test ls <TODO -l|wc -l >out>>out2<Makefile
}

void	add_heredoc(t_data *data, char *file, size_t index)
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
				tmp->hd_file = 0;
			add_file_node(data, tmp, file, 1);
			return ;
		}
		tmp = tmp->next;
	}
	add_file_node(data, tmp, file, 2);
}
