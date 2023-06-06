/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_infile_outfile.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 17:07:44 by rrebois           #+#    #+#             */
/*   Updated: 2023/06/06 12:04:57 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"

int	file_check_access(t_data *data, char *file, int i)
{
	if (i == 0)
	{
		data->fdin = open(file, O_RDONLY);
		if (access(file, F_OK) != 0 || access(file, R_OK) != 0 || \
		data->fdin < 0)
		{
			ft_error_file(file, 0);
			return (FILE_ERROR);
		}
		data->maxfdin = data->fdin;
		return (SUCCESS);
	}
	else if (i == 1)
		data->fdout = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	else
		data->fdout = open(file, O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (access(file, F_OK) != 0 || access(file, W_OK) != 0 || data->fdout < 0)
	{
		ft_error_file(file, 1);
		return (FILE_ERROR);
	}
	data->maxfdout = data->fdout;
	return (SUCCESS);
}

int	check_redirection(t_data *data, char *token, char *file, size_t index)
{
	int	valid;

	valid = 0;
	if (ft_strncmp(token, ">", 1) == 0 && ft_strlen(token) == 1)
	{
		valid = file_check_access(data, file, 1);
		add_outfile(data, file, index, valid);
	}
	else if (ft_strncmp(token, ">>", 2) == 0 && ft_strlen(token) == 2)
	{
		valid = file_check_access(data, file, 2);
		add_outfile(data, file, index, valid);
	}
	else if (ft_strncmp(token, "<", 1) == 0 && ft_strlen(token) == 1)
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
		if (data->lexer == NULL)
			break ;
		if (tmp->token != NULL && ft_strncmp(tmp->token, "|", 1) != 0)
			continue ;
		tmp = tmp->next;
	}
	add_pipes_redir(data);










	// test
	size_t len = 0;
	if (lstlen(data->lexer) > 0)
	{

	tmp = data->lexer;
	while (tmp != NULL)
	{
		len++;
		tmp = tmp->next;
	}
	printf("len lexer: %ld\n", len);

	t_lexer	*tmp2;
	tmp2 = data->lexer;
	while (tmp2 != NULL)
	{
		ft_printf("\n\n");
// if (tmp2->word != NULL)
	ft_printf("word node: %s\n", tmp2->word);
// else
	ft_printf("token node: %s\n", tmp2->token);
printf("index: %ld\n", tmp2->index);
ft_printf("infile: %s\n", tmp2->infile);
ft_printf("outfile: %s\n", tmp2->outfile);
ft_printf("hdoc: %d\n",tmp2->hd_file);
// ft_printf("hdoc count: %d\n",tmp2->hd->hd_count);
		tmp2 = tmp2->next;
	}}
	else
		printf("len lexer: %ld\n", len);
// 	// end test ls <TODO -l|wc -l >out>>out2<Makefile
}
