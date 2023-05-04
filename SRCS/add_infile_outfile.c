/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_infile_outfile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:07:44 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/04 15:31:01 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	file_check_access(t_data *data, char *file, int i)
{
	if (i == 0) // infile >
	{
		data->fdin = open(file, O_RDONLY);
		if (access(file, F_OK) != 0 || access(file, R_OK) != 0 || \
		data->fdin < 0)
		{
			ft_error_file(data->fdin, file, 0);
			return (FILE_ERROR);
		}
		return (SUCCESS);
	}
	else if (i == 1) // outfile >
		data->fdout = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else //append
		data->fdout = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (access(file, F_OK) != 0 || access(file, W_OK) != 0 || data->fdout < 0)
	{
		ft_error_file(data->fdout, file, 1);
		return (FILE_ERROR);
	}
	return (SUCCESS);
}
// WARNING: if infile does not exist: program writing the good error code
// BUT the program still adds the file as infile! Not good
// cat <TODO |wc -l <Makefiles >out bash does not create out cuz Makefiles error
// cat <TODO |wc -l >out <Makefiles bash creates out
int	check_redirection(t_data *data, char *token, char *file, size_t index)
{
	int	valid;

	valid = 0;
	if (ft_strncmp(token, ">", 1) == 0 && ft_strlen(token) == 1) // outfile
	{
		valid = file_check_access(data, file, 1);
		add_outfile(data, file, index, valid);
	}
	else if (ft_strncmp(token, ">>", 2) == 0 && ft_strlen(token) == 2) // out app
	{
		valid = file_check_access(data, file, 2);
		add_outfile(data, file, index, valid);
	}
	else if (ft_strncmp(token, "<", 1) == 0 && ft_strlen(token) == 1) // inf
	{
		valid = file_check_access(data, file, 0);
		add_infile(data, file, index, valid);
	}
	else
		add_heredoc(data, file, index);
	return (valid);
}

void	remove_nodes_redirection(t_data *data, size_t index)
{
	if (index == 0 || lstlen(data->lexer) == 2)
		remove_front_nodes(data, lstlen(data->lexer));
	else if (index + 1 == lstlen(data->lexer) - 1 && lstlen(data->lexer) > 2)
		remove_back_nodes(data);
	else
		remove_middle_nodes(data, index);
}

void	files_validity(t_data *data, t_lexer *tmp, int *valid)
{
	if (*valid != SUCCESS)
	{
		if (ft_strncmp(tmp->token, "<", 1) != 0)
			add_outfile(data, tmp->next->word, tmp->index, *valid);
		remove_nodes_redirection(data, tmp->index);
	}
	else
	{
		*valid = check_redirection(data, tmp->token, tmp->next->word, \
		tmp->index);
		remove_nodes_redirection(data, tmp->index);
	}
	add_index(data);
}

void	token_check(t_data *data)
{
	t_lexer	*tmp;
	int		valid;

	heredoc_count(data);
	valid = 0;
	tmp = data->lexer;
	while (tmp != NULL)
	{
		if (tmp->token != NULL && ft_strncmp(tmp->token, "|", 1) == 0)
			valid = 0;
		if (tmp->token != NULL && ft_strncmp(tmp->token, "|", 1) != 0)
		{
			files_validity(data, tmp, &valid);
			tmp = data->lexer;
		}
		if (tmp->token != NULL && ft_strncmp(tmp->token, "|", 1) != 0)
			continue ;
		tmp = tmp->next;
	}


// 	// test
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
// // if (tmp2->lexer->word != NULL)
// 	ft_printf("word node: %s\n", tmp2->lexer->word);
// // else
// 	ft_printf("token node: %s\n", tmp2->lexer->token);
// printf("index: %ld\n", tmp2->lexer->index);
// ft_printf("infile: %s\n", tmp2->lexer->infile);
// ft_printf("outfile: %s\n", tmp2->lexer->outfile);
// ft_printf("hdoc: %d\n",tmp2->lexer->hd_file);
// 		tmp2->lexer = tmp2->lexer->next;
// 	}}
	// end test ls <TODO -l|wc -l >out>>out2<Makefile
}
