/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_infile_outfile_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rrebois <rrebois@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:27:51 by rrebois           #+#    #+#             */
/*   Updated: 2023/05/10 09:18:57 by rrebois          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../incs/minishell.h"
//ls <TODO | wc <Makefile >outer | test >out working fiiiiiiine !!!!!
void	add_file_node(t_data *data, t_lexer *lexer, char *file, int i)
{
	if (i == 0)
		lexer->infile = ft_strdup(file);
	else
	{
		if (lexer->infile != NULL)
		{
			free(lexer->infile);
			lexer->infile = NULL;
		}
		lexer->hd_file = 1;
		data->hd->LIMITER[data->hd->heredoc] = ft_strdup(file);
		lexer->hd_number = data->hd->heredoc;
		data->hd->heredoc++;
	}
}

t_lexer	*find_start(t_lexer *tmp)
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

void	add_infile(t_data *data, char *file, size_t index, int valid)
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
			complete_inf_data(data, tmp, file, valid);
			return ;
		}
		tmp = tmp->next;
	}//ajouter node avec derniere redir dans le cas ou ls |>out
}

void	add_outfile(t_data *data, char *file, size_t index, int valid)
{
	t_lexer	*tmp; // si multiples inf or

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
			complete_out_data(data, tmp, file, valid);
			return ;
		}
		tmp = tmp->next;
	}
}

void	ft_error_file(int fd, char *file, int i)
{
	if (fd < 0)
	{
		printf("minishell: %s: No such file or directory\n", file);
		return ;
	}
	else if (i == 0)
	{
		if (access(file, F_OK) != 0)
			printf("minishell: %s: No such file or directory\n", file);
		else if (access(file, R_OK) != 0)
			ft_printf("minishell: %s: Permission denied\n", file);
	}
	else
	{
		if (access(file, F_OK) != 0)
			printf("minishell: %s: No such file or directory\n", file);
		else if (access(file, W_OK) != 0)
			ft_printf("minishell: %s: Permission denied\n", file);
	}
}
