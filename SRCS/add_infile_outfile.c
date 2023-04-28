/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_infile_outfile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:07:44 by rrebois           #+#    #+#             */
/*   Updated: 2023/04/28 12:32:02 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

char	*filename_quote_removal(char *file)
{
	char	*filename;

	filename = str_quotes_removal(file);
	return (filename);
}

void	file_check_access(t_data *data, char *file, int i)
{
	if (i == 0) // infile >
	{
		data->fdin = open(file, O_RDONLY);
		if (access(file, F_OK) != 0)
			printf("minishell: %s: No such file or directory\n", file);
		else if (access(file, R_OK) != 0)
			ft_printf("minishell: %s: Permission denied\n", file);
	}
	else if (i == 1) // outfile >
	{
		data->fdout = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (access(file, F_OK) != 0)
			printf("minishell: %s: No such file or directory\n", file);
		else if (access(file, W_OK) != 0)
			ft_printf("minishell: %s: Permission denied\n", file);
	}
	else if (i == 2) // outfile append >>
	{
		data->fdout = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (access(file, F_OK) != 0)
			printf("minishell: %s: No such file or directory\n", file);
		else if (access(file, W_OK) != 0)
			ft_printf("minishell: %s: Permission denied\n", file);
	}
}

void	check_redirection(t_data *data, char *token, char *filename)
{
	if (ft_strncmp(token, ">", 1) == 0 && ft_strlen(token) == 1) // outfile
	{
		file_check_access(data, filename, 1);
		add_outfile(data, filename);
	}
	else if (ft_strncmp(token, ">>", 2) == 0 && ft_strlen(token) == 2) // out app
	{
		file_check_access(data, filename, 2);
		add_outfile(data, filename);
	}
	else if (ft_strncmp(token, "<", 1) == 0 && ft_strlen(token) == 1) // inf
	{
		file_check_access(data, filename, 0);
		add_infile(data, filename, 0);
	}
	else
		add_infile(data, filename, 1);
}

void	remove_nodes_redirection(t_data *data, size_t index)
{
	if (index == 0 || lstlen(data->lexer) == 2)
		remove_front_nodes(data);
	else if (index + 1 == lstlen(data->lexer) - 1 && lstlen(data->lexer) > 2)
		remove_back_nodes(data);
	else
		remove_middle_nodes(data, index);
}

void	token_check(t_data *data) // On a un segfault ici!
{
	t_lexer	*tmp;

	heredoc_count(data);
	// //test
	// size_t len;
	// len = 0;
	// tmp = data->lexer;
	// while (tmp != NULL)
	// {
	// 	len++;
	// 	tmp = tmp->next;
	// }
	// printf("len: %ld\n", len);
	// //endtest

	tmp = data->lexer;
	while (tmp != NULL)
	{
		if (tmp->token != NULL && ft_strncmp(tmp->token, "|", 1) != 0)
		{
			check_redirection(data, tmp->token, tmp->next->word);
			remove_nodes_redirection(data, tmp->index);
			add_index(data);
			tmp = data->lexer;
			continue ;
		}
		tmp = tmp->next;
	}
	check_heredoc(data);


// 	// test
// 	if (lstlen(data->lexer) > 0)
// 	{
// 	len = 0;
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
// ft_printf("LIMITER: %s\n",tmp2->lexer->LIMITER);
// ft_printf("hdoc: %d\n",tmp2->heredoc);
// 		tmp2->lexer = tmp2->lexer->next;
// 	}}
	// end test ls <TODO -l|wc -l >out>>out2<Makefile
}
